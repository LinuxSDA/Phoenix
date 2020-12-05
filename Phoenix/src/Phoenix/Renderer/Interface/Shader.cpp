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
    std::unique_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    PX_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLShader>(vertexSrc, fragmentSrc);
        }

        PX_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
