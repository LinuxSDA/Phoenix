//
//  Renderer2D.cpp
//  Phoenix
//
//  Created by SD on 27/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "Renderer2D.hpp"
#include "RenderCommand.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Phoenix
{
    Scope<Renderer2D::Renderer2DData> Renderer2D::s_Data = nullptr;


    Renderer2D::Renderer2DData::Renderer2DData() : NumVertices(4),
                                                   NumIndices(6),
                                                   MaxSupportedQuads(10000),
                                                   MaxSupportedVertices(NumVertices * MaxSupportedQuads),
                                                   MaxSupportedIndicies(NumIndices * MaxSupportedQuads),
                                                   MaxSupportedTextures(RenderCommand::GetMaxSupportedTextureSlots()),
                                                   QuadVertexArray(nullptr),
                                                   QuadVertexBuffer(nullptr),
                                                   QuadShader(nullptr),
                                                   WhiteTexture(nullptr),
                                                   WhiteTextureSlot(0),
                                                   NextAvailableTextureSlot(1),
                                                   BaseQuadVertices(-0.5f, -0.5f, 0.0f, 1.0f,
                                                                     0.5f, -0.5f, 0.0f, 1.0f,
                                                                     0.5f,  0.5f, 0.0f, 1.0f,
                                                                    -0.5f,  0.5f, 0.0f, 1.0f),
                                                   BaseQuadTexCoords(0.0f, 0.0f,
                                                                     1.0f, 0.0f,
                                                                     1.0f, 1.0f,
                                                                     0.0f, 1.0f),
                                                   BaseQuadIndices( { 0, 1, 2,
                                                                      2, 3, 0} ),
                                                   QuadIndex(0)
    {
    }


    void Renderer2D::Init()
    {
        PX_PROFILE_FUNCTION();

        s_Data = CreateScope<Renderer2DData>();

        s_Data->QuadVertexArray = VertexArray::Create();

        s_Data->QuadVertexBuffer = VertexBuffer::Create(s_Data->MaxSupportedVertices * sizeof(QuadVertex));

        s_Data->QuadVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float2, "a_UV" },
            { ShaderDataType::Float,  "a_TexID" },
            { ShaderDataType::Float,  "a_TileCount" },
        });
        
        s_Data->QuadVertexArray->AddVertexBuffer(s_Data->QuadVertexBuffer);
        s_Data->QuadVertexData.resize(s_Data->MaxSupportedVertices);


        std::vector<uint32_t> quadIndices;
        quadIndices.reserve(s_Data->MaxSupportedIndicies);

        for (uint32_t i = 0; i < s_Data->MaxSupportedQuads; i++)
        {
            for (auto index: s_Data->BaseQuadIndices)
                quadIndices.emplace_back(i * s_Data->NumVertices + index);
        }
        
        Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices.data(), s_Data->MaxSupportedIndicies);
        s_Data->QuadVertexArray->SetIndexBuffer(quadIB);

        /* TODO: Will need segregation here for different platform shaders */
        s_Data->QuadShader = Shader::Create("../../Phoenix/src/Phoenix/Renderer/OpenGL/shaders/Texture.glsl");
        s_Data->QuadShader->Bind();
        
        s_Data->WhiteTexture = Texture2D::Create(1, 1, Texture2D::Format::RGBA);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data->WhiteTexture->Bind(s_Data->WhiteTextureSlot);
        s_Data->WhiteTexture->SetData((uint8_t*)&whiteTextureData, sizeof(whiteTextureData));
        
        s_Data->TextureSlotBindings.resize(s_Data->MaxSupportedTextures);
        s_Data->TextureSlotBindings[s_Data->WhiteTextureSlot] = s_Data->WhiteTexture;

        std::vector<int> samplers(s_Data->MaxSupportedTextures);

        for (int index = 0; index < s_Data->MaxSupportedTextures; index++)
            samplers[index] = index;

        s_Data->QuadShader->SetIntArray("u_Textures", samplers.data(), (uint32_t)samplers.size());
    }
    
    void Renderer2D::Shutdown()
    {
        
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        PX_PROFILE_FUNCTION();
        
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        ResetBatchMetadata();
    }

    void Renderer2D::Flush()
    {
        PX_PROFILE_FUNCTION();

        // Bind textures
        for (uint32_t i = 0; i < s_Data->NextAvailableTextureSlot; i++)
            s_Data->TextureSlotBindings[i]->Bind(i);

        s_Data->QuadVertexBuffer->SetData(s_Data->QuadVertexData.data(), s_Data->QuadIndex * sizeof(QuadVertex) * s_Data->NumVertices);
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray, s_Data->NumIndices * s_Data->QuadIndex);

        s_Data->Stats.DrawCalls++;
        ResetBatchMetadata();
    }

    void Renderer2D::EndScene()
    {
        PX_PROFILE_FUNCTION();
        
        Flush();
    }

    void Renderer2D::ResetBatchMetadata()
    {
        PX_PROFILE_FUNCTION();

        s_Data->QuadIndex = 0;
        s_Data->NextAvailableTextureSlot = 1;
    }

    glm::mat4 Renderer2D::CreateQuadVertices(const glm::vec3& center, float radians, const glm::vec2& size)
    {
        PX_PROFILE_FUNCTION();

        return glm::translate(glm::mat4(1.0f), center) *
               glm::rotate(glm::mat4(1.0f), radians, glm::vec3(0.0f, 0.0f, 1.0f)) *
               glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f)) *
               s_Data->BaseQuadVertices;
    }

    void Renderer2D::DrawQuad(const QuadProperties& properties)
    {
        PX_PROFILE_FUNCTION();

        if(s_Data->QuadIndex > (s_Data->MaxSupportedQuads - 1))
            Flush();
        
        if(s_Data->NextAvailableTextureSlot > (s_Data->MaxSupportedTextures - 1))
            Flush();
        
        const auto& currentTexture = properties.Texture ? properties.Texture : s_Data->WhiteTexture;

        int32_t textureIndex = -1;
        
        for (int32_t i = 0; i < s_Data->NextAvailableTextureSlot; i++)
        {
            if (s_Data->TextureSlotBindings[i]->Compare(*currentTexture))
            {
                textureIndex = i;
                break;
            }
        }

        if (textureIndex == -1)
        {
            textureIndex = s_Data->NextAvailableTextureSlot;
            s_Data->TextureSlotBindings[s_Data->NextAvailableTextureSlot] = currentTexture;
            s_Data->NextAvailableTextureSlot++;
        }

        PX_ENGINE_ASSERT(textureIndex != -1, "Wrong texture index!");
        
        glm::mat4 vertices = CreateQuadVertices(properties.Center, properties.Radians, properties.Scale);
        
        for (int vID = 0; vID < s_Data->NumVertices; vID++)
        {
            s_Data->QuadVertexData[s_Data->QuadIndex * s_Data->NumVertices + vID].Position   = vertices[vID];
            s_Data->QuadVertexData[s_Data->QuadIndex * s_Data->NumVertices + vID].Color      = properties.Color;
            s_Data->QuadVertexData[s_Data->QuadIndex * s_Data->NumVertices + vID].TexCoord   = s_Data->BaseQuadTexCoords[vID];
            s_Data->QuadVertexData[s_Data->QuadIndex * s_Data->NumVertices + vID].TexID      = static_cast<float>(textureIndex);
            s_Data->QuadVertexData[s_Data->QuadIndex * s_Data->NumVertices + vID].TileFactor = properties.TilingFactor;
        }

        s_Data->QuadIndex++;
        s_Data->Stats.QuadCount++;
    }

    void Renderer2D::ResetStats()
    {
        s_Data->Stats.DrawCalls = 0;
        s_Data->Stats.QuadCount = 0;
    }

    Renderer2D::Statistics Renderer2D::GetStats()
    {
        return s_Data->Stats;
    }

}
