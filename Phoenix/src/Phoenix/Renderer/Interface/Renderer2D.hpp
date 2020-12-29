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
#include "Texture.hpp"

namespace Phoenix
{
    struct QuadProperties
    {
        float Radians        = 0.0f;
        glm::vec3 Position   = glm::vec3(0.0f);
        glm::vec2 Scale      = glm::vec2(1.0f);
        glm::vec4 Color      = glm::vec4(1.0f);
        Ref<Texture> Texture = nullptr;
        float TilingFactor   = 1.0f;
                
    public:
        inline void SetPosition(const glm::vec2& position) { Position = glm::vec3(position, 0.0f); }
        inline void SetPosition(const glm::vec3& position) { Position = position; }
        inline void Reset()
        {
            Radians      = 0.0f;
            Position     = glm::vec3(0.0f);
            Scale        = glm::vec2(1.0f);
            Color        = glm::vec4(1.0f);
            Texture      = nullptr;
            TilingFactor = 1.0f;
        }
    };

    class Renderer2D
    {
    public:
        Renderer2D() = delete;

        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        // Primitives
        static void DrawQuad(const QuadProperties& properties);

    private:
        static glm::mat4 CalculateTRS(const glm::vec3& position, float radians, const glm::vec2& size);

    private:
        struct Renderer2DData
        {
            Ref<VertexArray>   QuadVertexArray;
            Ref<Shader>        QuadShader;
            Ref<Texture2D>     WhiteTexture;
        };

        static Scope<Renderer2DData> s_Data;
    };
}
