//
//  VertexArray.cpp
//  Phoenix
//
//  Created by SD on 30/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "VertexArray.hpp"

#include "Renderer.hpp"
#include "Phoenix/Renderer/OpenGL/OpenGLVertexArray.hpp"

namespace Phoenix
{
    Scope<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    PX_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLVertexArray>();
        }

        PX_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
