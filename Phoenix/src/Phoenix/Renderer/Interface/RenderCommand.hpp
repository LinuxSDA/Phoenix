//
//  RenderCommand.h
//  Phoenix
//
//  Created by SD on 30/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "RendererAPI.hpp"

namespace Phoenix
{
    class RenderCommand
    {
    public:

        inline static void Init()
        {
            s_RendererAPI->Init();
        }

        inline static void SetClearColor(const glm::vec4& color)
        {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear()
        {
            s_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const Ref<const VertexArray>& vertexArray)
        {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_RendererAPI->SetViewport(x, y, width, height);
        }

    private:
        static Scope<RendererAPI> s_RendererAPI;
    };
}
