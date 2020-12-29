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
    PX_PROFILE_FUNCTION();

    m_CheckerboardTexture = Phoenix::Texture2D::Create("../../Sandbox/assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Phoenix::Timestep ts)
{
    PX_PROFILE_FUNCTION();
    // Render
    Phoenix::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Phoenix::RenderCommand::Clear();

    Phoenix::QuadProperties quadProperties;
    
    Phoenix::Renderer2D::BeginScene(Phoenix::Application::GetApplication().GetOrthographicCamera());
    {
        quadProperties.Scale = {0.5f, 0.5f};
        quadProperties.Color = m_SquareColor;
        Phoenix::Renderer2D::DrawQuad(quadProperties);

        quadProperties.Reset();
        quadProperties.Position = {0.0f, 0.0f, -0.1f};
        quadProperties.Scale = {15.0f, 15.0f};
        quadProperties.Texture = m_CheckerboardTexture;
        quadProperties.TilingFactor = 15.0f;
        Phoenix::Renderer2D::DrawQuad(quadProperties);

        quadProperties.Reset();
        quadProperties.SetPosition({-1.0f, 1.0f});
        quadProperties.Radians = M_PI_4;
        quadProperties.Color = {1.0, 0.2, 0.4, 1.0f};
        Phoenix::Renderer2D::DrawQuad(quadProperties);
    }
    Phoenix::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    PX_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Phoenix::Event& e)
{

}
