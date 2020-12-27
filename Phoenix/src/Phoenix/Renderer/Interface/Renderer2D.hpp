//
//  Renderer2D.hpp
//  Phoenix
//
//  Created by SD on 27/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "OrthographicCamera.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

namespace Phoenix
{
    class Renderer2D
    {
    public:
        Renderer2D() = delete;

        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        // Primitives
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        
    private:
        struct Renderer2DData
        {
            Ref<VertexArray> QuadVertexArray;
            Ref<Shader> FlatColorShader;
        };

        static Scope<Renderer2DData> s_Data;
    };
}
