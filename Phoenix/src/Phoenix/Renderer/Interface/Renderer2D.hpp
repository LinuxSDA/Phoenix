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
    class QuadProperties
    {
    public:
        QuadProperties() { Reset(); }

        inline void Reset()
        {
            m_Radians      = 0.0f;
            m_Center       = glm::vec3(0.0f);
            m_Scale        = glm::vec2(1.0f);
            m_Color        = glm::vec4(1.0f);
            m_TilingFactor = 1.0f;
            m_Texture      = nullptr;
            m_TextureCoord = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        }

        inline void SetCenter(const glm::vec2& center)  { m_Center = glm::vec3(center.x, center.y, 0.0f); }
        inline void SetCenter(const glm::vec3& center)  { m_Center = center; }
        inline void SetScale(const glm::vec2& scale)    { m_Scale = scale; }
        inline void SetRotation(float radians)          { m_Radians = radians; }
        inline void SetColor(const glm::vec4& color)    { m_Color = color; }
        inline void SetTilingFactor(float factor)       { m_TilingFactor = factor; }
        inline void SetTexture(Ref<Texture2D> texture)  { m_Texture = texture; m_TextureCoord = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);}
        /* sub texture coords: {bottomX, bottomY, width, height} */
        inline void SetSubTexture(Ref<Texture2D> texture, const glm::vec4& coords) { m_Texture = texture; m_TextureCoord = coords; }
        
        
        inline const glm::vec3& GetCenter()        const { return m_Center; }
        inline const glm::vec2& GetScale()         const { return m_Scale; }
        inline       float      GetRotation()      const { return m_Radians; }
        inline const glm::vec4& GetColor()         const { return m_Color; }
        inline       float      GetTilingFactor()  const { return m_TilingFactor;}
        inline   Ref<Texture2D> GetTexture()       const { return m_Texture; }
        /* sub texture coords: {bottomX, bottomY, width, height} */
        inline const glm::vec4& GetTextureCoords() const { return m_TextureCoord; }

    private:
        float           m_Radians         = 0.0f;
        glm::vec3       m_Center          = glm::vec3(0.0f);
        glm::vec2       m_Scale           = glm::vec2(1.0f);
        glm::vec4       m_Color           = glm::vec4(1.0f);
        float           m_TilingFactor    = 1.0f;
        Ref<Texture2D>  m_Texture         = nullptr;
        glm::vec4       m_TextureCoord    = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

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
        static glm::vec2 GetVertexTextureCoordinates(const glm::vec4& subCoords, int vertexID);

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
            std::vector<uint32_t>       BaseQuadIndices;
            
            std::vector<QuadVertex>     QuadVertexData;
            uint32_t                    QuadIndex;
            
            Statistics                  Stats;

            Renderer2DData();
        };

        static Scope<Renderer2DData> s_Data;
    };
}
