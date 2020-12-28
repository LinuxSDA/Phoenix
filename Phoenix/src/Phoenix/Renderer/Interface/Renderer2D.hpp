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
    class Renderer2D
    {
    public:
        Renderer2D() = delete;

        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        // Primitives
        static void DrawQuad(const glm::vec2& position, float radians, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, float radians, const glm::vec2& size, const glm::vec4& color);

        static void DrawQuad(const glm::vec2& position, float radians, const glm::vec2& size, const Ref<Texture>& texture, uint8_t tileCount = 1);
        static void DrawQuad(const glm::vec3& position, float radians, const glm::vec2& size, const Ref<Texture>& texture, uint8_t tileCount = 1);

        static void DrawQuad(const glm::mat4& TRS, const glm::vec4& color);
        static void DrawQuad(const glm::mat4& TRS, const Ref<Texture>& texture, uint8_t tileCount = 1);

    private:
        static glm::mat4 CalculateTRS(const glm::vec3& position, float radians, const glm::vec2& size);

    private:
        struct Renderer2DData
        {
            Ref<VertexArray>   QuadVertexArray;
            Ref<ShaderLibrary> ShaderLib;
        };

        static Scope<Renderer2DData> s_Data;
    };
}
