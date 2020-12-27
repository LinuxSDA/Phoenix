//
//  Buffer.cpp
//  Phoenix
//
//  Created by SD on 30/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "Buffer.hpp"
#include "Renderer.hpp"

#include "Phoenix/Renderer/OpenGL/OpenGLBuffer.hpp"

namespace Phoenix
{
    Scope<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    PX_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateScope<OpenGLVertexBuffer>(vertices, count);
        }

        PX_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Scope<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    PX_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateScope<OpenGLIndexBuffer>(indices, count);
        }

        PX_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
