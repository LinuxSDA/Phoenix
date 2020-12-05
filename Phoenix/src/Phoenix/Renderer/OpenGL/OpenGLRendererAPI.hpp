//
//  OpenGLRendererAPI.hpp
//  Phoenix
//
//  Created by SD on 30/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Phoenix/Renderer/Interface/RendererAPI.hpp"

namespace Phoenix
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };
}
