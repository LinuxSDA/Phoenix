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
        inline static void SetClearColor(const glm::vec4& color)
        {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear()
        {
            s_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const std::shared_ptr<const VertexArray>& vertexArray)
        {
            s_RendererAPI->DrawIndexed(vertexArray);
        }
        
    private:
        static std::unique_ptr<RendererAPI> s_RendererAPI;
    };
}
