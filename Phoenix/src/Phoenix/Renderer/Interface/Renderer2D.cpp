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
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {
        
    }

    glm::mat4 Renderer2D::CalculateTRS(const glm::vec3& position, float radians, const glm::vec2& size)
    {
        glm::mat4 TRS = glm::translate(glm::mat4(1.0f), position) *
                        glm::rotate(glm::mat4(1.0f), radians, glm::vec3(0, 0, 1)) *
                        glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

        return TRS;
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, float radians, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, radians, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, float radians, const glm::vec2& size, const glm::vec4& color)
    {
        glm::mat4 TRS = CalculateTRS(position, radians, size);
        DrawQuad(TRS, color);
    }

    void Renderer2D::DrawQuad(const glm::mat4& TRS, const glm::vec4& color)
    {
        s_Data->QuadShader->Bind();
        s_Data->WhiteTexture->Bind(0);

        s_Data->QuadShader->SetFloat4("u_Color", color);
        s_Data->QuadShader->SetInt("u_Texture", 0);
        s_Data->QuadShader->SetMat4("u_Transform", TRS);
        s_Data->QuadShader->SetInt("u_TileCount", 1);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, float radians, const glm::vec2& size, const Ref<Texture>& texture, uint8_t tileCount)
    {
        DrawQuad({ position.x, position.y, 0.0f }, radians, size, texture, tileCount);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, float radians, const glm::vec2& size, const Ref<Texture>& texture, uint8_t tileCount)
    {
        glm::mat4 TRS = CalculateTRS(position, radians, size);
        DrawQuad(TRS, texture, tileCount);
    }

    void Renderer2D::DrawQuad(const glm::mat4& TRS, const Ref<Texture>& texture, uint8_t tileCount)
    {
        s_Data->QuadShader->Bind();
        texture->Bind(0);

        s_Data->QuadShader->SetFloat4("u_Color", glm::vec4(1.0f));
        s_Data->QuadShader->SetInt("u_Texture", 0);
        s_Data->QuadShader->SetMat4("u_Transform", TRS);
        s_Data->QuadShader->SetInt("u_TileCount", tileCount);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
}
