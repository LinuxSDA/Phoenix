//
//  Renderer.hpp
//  Phoenix
//
//  Created by SD on 29/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "RenderCommand.hpp"

namespace Phoenix
{
    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& va);
        
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
}
