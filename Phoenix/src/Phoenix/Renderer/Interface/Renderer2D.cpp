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

namespace Phoenix
{
    Scope<Renderer2D::Renderer2DData> Renderer2D::s_Data = nullptr;

    void Renderer2D::Init()
    {
        PX_PROFILE_FUNCTION();

        s_Data = CreateScope<Renderer2DData>();
        
        s_Data->QuadVertexArray = VertexArray::Create();

        std::vector<float> squareVertices {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices.data(), (uint32_t)squareVertices.size());
        squareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord" }
        });
        
        s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

        std::vector<uint32_t> squareIndices { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices.data(), (uint32_t)squareIndices.size());
        s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

        /* TODO: These shaders should be in Phoenix instead of sandbox*/
        s_Data->QuadShader = Shader::Create("../../Sandbox/assets/shaders/Texture.glsl");
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetInt("u_Texture", 0);
        
        s_Data->WhiteTexture = Texture2D::Create(1, 1, Texture2D::Format::RGBA);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data->WhiteTexture->Bind(0);
        s_Data->WhiteTexture->SetData((uint8_t*)&whiteTextureData, sizeof(whiteTextureData));
    }
    
    void Renderer2D::Shutdown()
    {
        
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        PX_PROFILE_FUNCTION();

        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {
        
    }

    glm::mat4 Renderer2D::CalculateTRS(const glm::vec3& position, float radians, const glm::vec2& size)
    {
        PX_PROFILE_FUNCTION();

        return glm::translate(glm::mat4(1.0f), position) *
               glm::rotate(glm::mat4(1.0f), radians, glm::vec3(0, 0, 1)) *
               glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
    }

    void Renderer2D::DrawQuad(const QuadProperties& properties)
    {
        PX_PROFILE_FUNCTION();
        
        glm::mat4 TRS = CalculateTRS(properties.Position, properties.Radians, properties.Scale);

        auto& currentTexture = properties.Texture ? properties.Texture : s_Data->WhiteTexture;
        int textureSlot = 0;

        currentTexture->Bind(textureSlot);
        
        s_Data->QuadShader->SetFloat4("u_Color", properties.Color);
        s_Data->QuadShader->SetInt("u_Texture", textureSlot);
        s_Data->QuadShader->SetMat4("u_Transform", TRS);
        s_Data->QuadShader->SetInt("u_TileCount", properties.TilingFactor);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

}
