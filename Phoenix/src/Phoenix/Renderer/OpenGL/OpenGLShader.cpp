//
//  OpenGLShader.cpp
//  Phoenix
//
//  Created by SD on 29/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "OpenGLShader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Phoenix
{
    const std::string OpenGLShader::k_TypeToken = "#type";
    const std::string OpenGLShader::k_VertexShader = "vertex";
    const std::string OpenGLShader::k_FragmentShader = "fragment";
    const std::string OpenGLShader::k_PixelShader = "pixel";

    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
        std::string source = ReadFile(filepath);
        auto shaderSources = PreProcess(source);
        Compile(shaderSources);
        
        // Extract name from filepath
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_Name(name)
    {
        std::map<GLenum, std::string> shaderSources;

        shaderSources[GL_VERTEX_SHADER] = vertexSrc;
        shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

        Compile(shaderSources);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    std::string OpenGLShader::ReadFile(const std::string& filepath)
    {
        std::ifstream inStream(filepath, std::ios::in | std::ios::binary);
        PX_ENGINE_ASSERT(inStream.good(), "Filepath invalid!");

        std::stringstream buffer;
        buffer << inStream.rdbuf();
        
        return buffer.str();
    }

    std::map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
    {
        std::map<GLenum, std::string> shaderSources;
        size_t pos = source.find(k_TypeToken);

        PX_ENGINE_ASSERT(pos != std::string::npos, "Token not found!");
        
        while (pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos);
            PX_ENGINE_ASSERT(eol != std::string::npos, "Syntax error!");

            size_t begin = pos + k_TypeToken.size() + 1;
            std::string type = source.substr(begin, eol - begin);
            PX_ENGINE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

            size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
            PX_ENGINE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
            pos = source.find(k_TypeToken, nextLinePos); //Start of next shader type declaration line

            shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
        }

        return shaderSources;
    }

    GLenum OpenGLShader::ShaderTypeFromString(const std::string& type)
    {
        if (type == k_VertexShader)
            return GL_VERTEX_SHADER;
        if (type == k_FragmentShader || type == k_PixelShader)
            return GL_FRAGMENT_SHADER;

        PX_ENGINE_ASSERT(false, "Unknown shader type!");
        return 0;
    }

    void OpenGLShader::Compile(const std::map<GLenum, std::string>& shaderSources)
    {
        GLuint program = glCreateProgram();
        std::vector<GLenum> glShaderIDs;
        glShaderIDs.reserve(shaderSources.size());
        
        for (const auto& kv : shaderSources)
        {
            GLenum type = kv.first;
            const std::string& source = kv.second;

            GLuint shader = glCreateShader(type);

            const GLchar* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                PX_ENGINE_ERROR("{0}", infoLog.data());
                PX_ENGINE_ASSERT(false, "Shader compilation failure!");
                break;
            }

            glAttachShader(program, shader);
            glShaderIDs.push_back(shader);
        }
        
        // Link our program
        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            
            for (auto id : glShaderIDs)
                glDeleteShader(id);

            PX_ENGINE_ERROR("{0}", infoLog.data());
            PX_ENGINE_ASSERT(false, "Shader link failure!");
            return;
        }

        for (auto id : glShaderIDs)
        {
            glDetachShader(program, id);
            glDeleteShader(id);
        }

        m_RendererID = program;
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, int value) const
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformFloat(const std::string& name, float value) const
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) const
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) const
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) const
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}
