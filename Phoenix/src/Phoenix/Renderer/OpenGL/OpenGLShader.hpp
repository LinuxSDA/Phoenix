//
//  OpenGLShader.hpp
//  Phoenix
//
//  Created by SD on 29/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Phoenix/Renderer/Interface/Shader.hpp"
#include <glad/glad.h>

namespace Phoenix
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual inline const std::string& GetName() const override { return m_Name;}

        virtual void SetInt(const std::string& name, int value) const override;
        virtual void SetIntArray(const std::string& name, int* values, uint32_t count) const override;

        virtual void SetFloat3(const std::string& name, const glm::vec3& value) const override;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) const override;

        virtual void SetMat3(const std::string& name, const glm::mat3& matrix) const override;
        virtual void SetMat4(const std::string& name, const glm::mat4& matrix) const override;


    private:
        virtual void UploadUniformInt(const std::string& name, int value) const;
        virtual void UploadUniformIntArray(const std::string& name, int* values, uint32_t count) const;

        virtual void UploadUniformFloat(const std::string& name, float value) const;
        virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value) const;
        virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value) const;
        virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value) const;

        virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;

    private:
        std::string ReadFile(const std::string& filepath);
        std::map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::map<GLenum, std::string>& shaderSources);
        
        static GLenum ShaderTypeFromString(const std::string& type);

    private:
        uint32_t m_RendererID = 0;
        std::string m_Name;

        static const std::string k_TypeToken;
        static const std::string k_VertexShader;
        static const std::string k_FragmentShader;
        static const std::string k_PixelShader;
    };
}
