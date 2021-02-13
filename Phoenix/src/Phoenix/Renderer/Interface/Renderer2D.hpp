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
        float           Radians         = 0.0f;
        glm::vec3       Center          = glm::vec3(0.0f);
        glm::vec2       Scale           = glm::vec2(1.0f);
        glm::vec4       Color           = glm::vec4(1.0f);
        Ref<Texture2D>  Texture         = nullptr;
        float           TilingFactor    = 1.0f;

    public:
        inline void Reset()
        {
            Radians      = 0.0f;
            Center       = glm::vec3(0.0f);
            Scale        = glm::vec2(1.0f);
            Color        = glm::vec4(1.0f);
            Texture      = nullptr;
            TilingFactor = 1.0f;
        }
    };

    class Renderer2D
    {
    public:
        struct Statistics
        {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;
        };

    public:
        Renderer2D() = delete;
        Renderer2D(const Renderer2D&) = delete;
        Renderer2D& operator=(const Renderer2D&) = delete;

        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void Flush();
        static void EndScene();

        // Primitives
        static void DrawQuad(const QuadProperties& properties);

        static Statistics GetStats();
        static void ResetStats();

    private:
        static glm::mat4 CreateQuadVertices(const glm::vec3& center, float radians, const glm::vec2& size);
        static void ResetBatchMetadata();

    private:
        
        struct QuadVertex
        {
            glm::vec3   Position;
            glm::vec4   Color;
            glm::vec2   TexCoord;
            float       TexID;
            float       TileFactor;
        };
        
        struct Renderer2DData
        {
            const uint8_t               NumVertices;
            const uint8_t               NumIndices;
            const uint32_t              MaxSupportedQuads;
            const uint32_t              MaxSupportedVertices;
            const uint32_t              MaxSupportedIndicies;
            const int32_t               MaxSupportedTextures;

            Ref<VertexArray>            QuadVertexArray;
            Ref<VertexBuffer>           QuadVertexBuffer;
            Ref<Shader>                 QuadShader;
            Ref<Texture2D>              WhiteTexture;

            int32_t                     WhiteTextureSlot;
            int32_t                     NextAvailableTextureSlot;
            std::vector<Ref<Texture2D>> TextureSlotBindings;

            glm::mat4                   BaseQuadVertices;
            glm::mat4x2                 BaseQuadTexCoords;
            std::vector<uint32_t>       BaseQuadIndices;
            
            std::vector<QuadVertex>     QuadVertexData;
            uint32_t                    QuadIndex;
            
            Statistics                  Stats;

            Renderer2DData();
        };

        static Scope<Renderer2DData> s_Data;
    };
}
