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
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Phoenix::Timestep ts)
{
    // Render
    Phoenix::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Phoenix::RenderCommand::Clear();

    Phoenix::Renderer2D::BeginScene(Phoenix::Application::GetApplication().GetOrthographicCamera());
    {
        Phoenix::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, m_SquareColor);
    }
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
