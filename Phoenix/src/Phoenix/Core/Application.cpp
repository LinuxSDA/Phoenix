//
//  Application.cpp
//  Phoenix
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"

#include "Application.hpp"
#include "Logger.hpp"
#include "Input.h"
#include "Timestep.h"

#include "Phoenix/Renderer/Interface/Renderer.hpp"

namespace Phoenix
{
    Application::ObserverPtr Application::m_ApplicationPointer = nullptr;

    Application::Application()
    {
        PX_ENGINE_ASSERT(m_ApplicationPointer == nullptr, "Application already exists!");

        m_ApplicationPointer = this;

        // Window //
        m_Window = Window::Create();
        PX_ENGINE_ASSERT(m_Window != nullptr, "Cannnot create window!");
        m_Window->SetEventCallback(PX_BIND_EVENT_FN(Application::OnEvent));
        
        Renderer::Init();
        
        // Camera Controller //
        float aspectRatio = (float)m_Window->GetWidth()/m_Window->GetHeight();
        Scope<CameraController> occ = CreateScope<OrthographicCameraController>(aspectRatio);
        PX_ENGINE_ASSERT(occ != nullptr, "Can not create camera class!");
        m_CameraControllerID = occ->GetLayerID();
        PushLayer(std::move(occ));
        
        // ImGUI Layer//
        Scope<ImGuiLayer> imGuiLayer = ImGuiLayer::Create();
        PX_ENGINE_ASSERT(imGuiLayer != nullptr, "Can not create imgui layer!");
        m_ImGuiLayerID = imGuiLayer->GetLayerID();
        PushOverlay(std::move(imGuiLayer));
    
    }

    const Window& Application::GetWindow() const
    {
        PX_ENGINE_ASSERT(m_Window != nullptr, "Window not intialized!");
        return *m_Window;
    }

    const OrthographicCamera& Application::GetOrthographicCamera() const
    {
        const CameraController& cameraController = static_cast<const CameraController&>(m_LayerStack.Get(m_CameraControllerID));
        return cameraController.GetCamera();
    }

    void Application::PushLayer(Scope<Layer> layer)
    {
        m_LayerStack.PushLayer(std::move(layer));
    }

    void Application::PushOverlay(Scope<Layer> layer)
    {
        m_LayerStack.PushOverlay(std::move(layer));
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        
        dispatcher.Dispatch<WindowCloseEvent>(PX_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(PX_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if(e.m_Handled)
                break;

            (*it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if(e.GetWidth() == 0 || e.GetHeight()== 0)
        {
            m_Minimized = true;
        }
        else
        {
            m_Minimized = false;
            Renderer::OnWindowResize(e.GetWidth() * m_Window->GetScaleFactor(), e.GetHeight() * m_Window->GetScaleFactor());
        }

        return false;
    }

    ImGuiLayer& Application::GetApplicationImGuiLayer()
    {
        ImGuiLayer& imGuiLayer = static_cast<ImGuiLayer&>(m_LayerStack.Get(m_ImGuiLayerID));
        return imGuiLayer;
    }

    void Application::Run()
    {
        auto& appImGuiLayer = GetApplicationImGuiLayer();

        while (m_Running)
        {
            float time = m_Window->GetCurrentTime();
            Timestep ts = time - m_LastFrameTime;
            m_LastFrameTime = time;
            
            if (!m_Minimized)
            {
                for (auto& layer : m_LayerStack)
                    layer->OnUpdate(ts);
            }

            appImGuiLayer.Begin();
            
            for (auto& layer : m_LayerStack)
                layer->OnImGuiRender();

            appImGuiLayer.End();
            
            m_Window->OnUpdate();
        }
    }
}
