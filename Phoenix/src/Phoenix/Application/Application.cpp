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

#include <glad/glad.h>

namespace Phoenix
{
    std::unique_ptr<Window> Application::m_Window;

    Application::Application()
    {
        PX_ENGINE_ASSERT(m_Window == nullptr, "Application already exists!");
        m_Window = Window::Create();
        PX_ENGINE_ASSERT(m_Window != nullptr, "Cannnot create window!");

        PX_ENGINE_TRACE(glGetString(GL_VERSION));

        m_Window->SetEventCallback(PX_BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application()
    {
        
    }

    const Window& Application::GetWindow()
    {
        PX_ENGINE_ASSERT(m_Window != nullptr, "Window not intialized!");
        return *m_Window;
    }

    void Application::PushLayer(std::unique_ptr<Layer> layer)
    {
        layer->OnAttach();
        m_LayerStack.PushLayer(std::move(layer));
    }

    void Application::PushOverlay(std::unique_ptr<Layer> layer)
    {
        layer->OnAttach();
        m_LayerStack.PushOverlay(std::move(layer));
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatch(e);
        
        dispatch.Dispatch<WindowCloseEvent>(PX_BIND_EVENT_FN(Application::OnWindowClose));
        
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin() && !e.m_Handled; )
        {
            (*--it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(1,1,0,1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            for (auto& layer : m_LayerStack)
                layer->OnUpdate();

            m_Window->OnUpdate();
        }
    }
}
