//
//  OpenGLRendererAPI.cpp
//  Phoenix
//
//  Created by SD on 30/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "OpenGLRendererAPI.hpp"

#include <glad/glad.h>

namespace Phoenix
{
    void OpenGLRendererAPI::Init()
    {
        PX_PROFILE_FUNCTION();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        PX_PROFILE_FUNCTION();

        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear()
    {
        PX_PROFILE_FUNCTION();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<const VertexArray>& vertexArray)
    {
        PX_PROFILE_FUNCTION();

        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        PX_PROFILE_FUNCTION();

        glViewport(x, y, width, height);
    }
}
