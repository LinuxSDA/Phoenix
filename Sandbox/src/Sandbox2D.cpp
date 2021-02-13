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
    m_PhoenixTexture      = Phoenix::Texture2D::Create("../../Branding/PhoenixLogo.png");
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
    
    Phoenix::Renderer2D::ResetStats();
    Phoenix::Renderer2D::BeginScene(Phoenix::Application::GetApplication().GetOrthographicCamera());
    {
        float increment = 0.2f;
        
        for(float i = -1.0f; i < 1.0f; i+=increment)
        {
            for(float j = -1.0f; j < 1.0f; j+=increment)
            {
                quadProperties.Scale = {increment, increment};
                quadProperties.Color = {((i+1)/2.f), 0.2f, (j + 1.f)/2.f, 1.0f};
                quadProperties.Center = {i, j, 0.0f};

                Phoenix::Renderer2D::DrawQuad(quadProperties);
            }
        }

        quadProperties.Reset();
        quadProperties.Center = {0.0f, 0.0f, -0.1f};
        quadProperties.Scale = {15.0f, 15.0f};
        quadProperties.Texture = m_CheckerboardTexture;
        quadProperties.TilingFactor = 15.0f;
        Phoenix::Renderer2D::DrawQuad(quadProperties);

        quadProperties.Reset();
        quadProperties.Center = {0.0f, 0.0f, 0.1f};
        quadProperties.Texture = m_PhoenixTexture;
        Phoenix::Renderer2D::DrawQuad(quadProperties);
    }
    Phoenix::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    PX_PROFILE_FUNCTION();

    ImGui::Begin("RenderStats");
    ImGui::Text("Quads %d", Phoenix::Renderer2D::GetStats().QuadCount);
    ImGui::Text("DrawCalls %d", Phoenix::Renderer2D::GetStats().DrawCalls);
    ImGui::Text("Frames %f", ImGui::GetIO().Framerate);
    ImGui::End();
}

void Sandbox2D::OnEvent(Phoenix::Event& e)
{

}
