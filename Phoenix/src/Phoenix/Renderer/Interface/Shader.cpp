//
//  Shader.cpp
//  Phoenix
//
//  Created by SD on 30/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "Shader.hpp"

#include "Renderer.hpp"
#include "Phoenix/Renderer/OpenGL/OpenGLShader.hpp"

namespace Phoenix
{

    Scope<Shader> Shader::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    PX_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLShader>(filepath);
        }

        PX_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }


    Scope<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    PX_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        PX_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }


    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        m_Shaders[shader->GetName()] = shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
    {
        Ref<Shader> shader = Shader::Create(filepath);
        Add(shader);

        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name) const
    {
        PX_ENGINE_ASSERT(Exists(name), "Shader doesn't exist!");
        return m_Shaders.at(name);
    }

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }

}
