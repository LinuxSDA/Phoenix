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

namespace Phoenix
{
    Scope<Renderer2D::Renderer2DData> Renderer2D::s_Data = nullptr;

    void Renderer2D::Init()
    {
        s_Data = CreateScope<Renderer2DData>();
        
        s_Data->QuadVertexArray = VertexArray::Create();

        std::vector<float> squareVertices {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices.data(), (uint32_t)squareVertices.size());
        squareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
        });
        
        s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

        std::vector<uint32_t> squareIndices { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices.data(), (uint32_t)squareIndices.size());
        s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

        /* TODO: This shader should be in Phoenix instead of sandbox*/
        s_Data->FlatColorShader = Shader::Create("../../Sandbox/assets/shaders/FlatColor.glsl");
    }
    
    void Renderer2D::Shutdown()
    {
        
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        s_Data->FlatColorShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
    }

    void Renderer2D::EndScene()
    {
        
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->UploadUniformFloat4("u_Color", color);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

}
