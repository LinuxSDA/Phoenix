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
    m_SpriteSheet         = Phoenix::Texture2D::Create("../../Sandbox/assets/spriteSheet/RPGpack_sheet.png");
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
        float increment = 0.1f;
        
        for(float i = -1.0f; i < 1.0f; i+=increment)
        {
            for(float j = -1.0f; j < 1.0f; j+=increment)
            {
                quadProperties.SetScale({increment, increment});
                quadProperties.SetColor({((i+1)/2.f), 0.2f, (j + 1.f)/2.f, 1.0f});
                quadProperties.SetCenter({i, j});

                Phoenix::Renderer2D::DrawQuad(quadProperties);
            }
        }

        quadProperties.Reset();
        quadProperties.SetCenter({0.0f, 0.0f, -0.1f});
        quadProperties.SetScale({15.0f, 15.0f});
        quadProperties.SetTexture(m_CheckerboardTexture);
        quadProperties.SetTilingFactor(15.0f);
        Phoenix::Renderer2D::DrawQuad(quadProperties);

        quadProperties.Reset();
        quadProperties.SetCenter({0.0f, 0.0f, 0.1f});
        quadProperties.SetTexture(m_PhoenixTexture);
        Phoenix::Renderer2D::DrawQuad(quadProperties);

        quadProperties.Reset();
        quadProperties.SetCenter({0.6f, -0.6f, 0.2f});
        quadProperties.SetScale({0.4f, 0.8f});
        quadProperties.SetSubTexture(m_SpriteSheet, {0.0f, 128.0f/m_SpriteSheet->GetHeight(),
                                                    128.0f/m_SpriteSheet->GetWidth(), 256.0f/m_SpriteSheet->GetHeight()});
        Phoenix::Renderer2D::DrawQuad(quadProperties);
    }
    Phoenix::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    PX_PROFILE_FUNCTION();
    
    // Note: Switch this to true to enable dockspace
    static bool dockingEnabled = false;
    if (dockingEnabled)
    {
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        
        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        
        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;
        
        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();
        
        if (opt_fullscreen)
            ImGui::PopStyleVar(2);
        
        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        
        
        ImGui::Begin("RenderStats");
        ImGui::Text("Quads %d", Phoenix::Renderer2D::GetStats().QuadCount);
        ImGui::Text("DrawCalls %d", Phoenix::Renderer2D::GetStats().DrawCalls);
        ImGui::Text("Frames %f", ImGui::GetIO().Framerate);

        uint32_t textureID = m_CheckerboardTexture->GetRendererID();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ 256.0f, 256.0f });
        ImGui::End();
        
        ImGui::End();
    }
    else
    {
        ImGui::Begin("Settings");
        
        ImGui::Text("Quads %d", Phoenix::Renderer2D::GetStats().QuadCount);
        ImGui::Text("DrawCalls %d", Phoenix::Renderer2D::GetStats().DrawCalls);
        ImGui::Text("Frames %f", ImGui::GetIO().Framerate);

        uint32_t textureID = m_CheckerboardTexture->GetRendererID();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ 256.0f, 256.0f });
        ImGui::End();
    }
}

void Sandbox2D::OnEvent(Phoenix::Event& e)
{

}
