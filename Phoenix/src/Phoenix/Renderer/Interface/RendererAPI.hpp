//
//  RendererAPI.hpp
//  Phoenix
//
//  Created by SD on 30/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include <glm/glm.hpp>

#include "VertexArray.hpp"

namespace Phoenix
{
    class RendererAPI
    {

    public:
        enum class API
        {
            None = 0, OpenGL = 1
        };
        
        virtual ~RendererAPI() = default;
        
        virtual void Init() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;
        
        virtual void DrawIndexed(const Ref<const VertexArray>& vertexArray, uint32_t count = 0) = 0;
        
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        virtual int32_t GetMaxSupportedTextureSlots() = 0;

        inline static API GetAPI() {return s_API;}
        
    private:
        static API s_API;
    };
}
