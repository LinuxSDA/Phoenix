//
//  Sandbox2D.cpp
//  Sandbox
//
//  Created by SD on 27/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "Sandbox2D.hpp"
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
{
}

void Sandbox2D::OnAttach()
{
    m_SquareVA = Phoenix::VertexArray::Create();

    std::vector<float> squareVertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    Phoenix::Ref<Phoenix::VertexBuffer> squareVB;
    squareVB = Phoenix::VertexBuffer::Create(squareVertices.data(), (uint32_t)squareVertices.size());
    squareVB->SetLayout({
        { Phoenix::ShaderDataType::Float3, "a_Position" }
    });
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Phoenix::Ref<Phoenix::IndexBuffer> squareIB = Phoenix::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = Phoenix::Shader::Create("../../Sandbox/assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Phoenix::Timestep ts)
{

    // Render
    Phoenix::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Phoenix::RenderCommand::Clear();

    Phoenix::Renderer::BeginScene(Phoenix::Application::GetApplication().GetOrthographicCamera());

    m_FlatColorShader->Bind();
    m_FlatColorShader->UploadUniformFloat4("u_Color", m_SquareColor);

    Phoenix::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Phoenix::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Phoenix::Event& e)
{

}
