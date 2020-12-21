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
        
        // ImGUI Layer//
        auto imGuiLayer = ImGuiLayer::Create();
        PX_ENGINE_ASSERT(imGuiLayer != nullptr, "Can not create imgui layer!");
        m_ImGuiLayerID = imGuiLayer->GetLayerID();
        PushOverlay(std::move(imGuiLayer));
    }

    const Window& Application::GetWindow() const
    {
        PX_ENGINE_ASSERT(m_Window != nullptr, "Window not intialized!");
        return *m_Window;
    }

    void Application::PushLayer(std::unique_ptr<Layer> layer)
    {
        m_LayerStack.PushLayer(std::move(layer));
    }

    void Application::PushOverlay(std::unique_ptr<Layer> layer)
    {
        m_LayerStack.PushOverlay(std::move(layer));
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatch(e);
        
        dispatch.Dispatch<WindowCloseEvent>(PX_BIND_EVENT_FN(Application::OnWindowClose));
        
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

    ImGuiLayer& Application::GetApplicationImGuiLayer()
    {
        auto imGuiLayerOptional = m_LayerStack.Get(m_ImGuiLayerID);
        PX_ENGINE_ASSERT(imGuiLayerOptional, "ImGui Layer doesn't exist!");

        ImGuiLayer& imGuiLayer = static_cast<ImGuiLayer&>(imGuiLayerOptional->get());
        
        return imGuiLayer;
    }

    void Application::Run()
    {
        auto& appImGuiLayer = GetApplicationImGuiLayer();

        while (m_Running)
        {
            for (auto& layer : m_LayerStack)
                layer->OnUpdate();

            appImGuiLayer.Begin();
            
            for (auto& layer : m_LayerStack)
                layer->OnImGuiRender();

            appImGuiLayer.End();
            
            m_Window->OnUpdate();
        }
    }
}
