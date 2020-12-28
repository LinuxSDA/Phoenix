//
//  Texture.cpp
//  Phoenix
//
//  Created by SD on 23/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Phoenix/Renderer/OpenGL/OpenGLTexture.hpp"

namespace Phoenix
{
    Scope<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, Format format)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    PX_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateScope<OpenGLTexture2D>(width, height, format);
        }

        PX_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Scope<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    PX_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateScope<OpenGLTexture2D>(path);
        }

        PX_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
