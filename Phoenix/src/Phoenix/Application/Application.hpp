//
//  Application.hpp
//  Phoenix
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Core.h"

#include "Window.h"
#include "Phoenix/Application/ImGuiLayer.h"

#include "LayerStack.hpp"
#include "Phoenix/Events/Event.h"
#include "Phoenix/Events/ApplicationEvent.h"
#include "Phoenix/Renderer/Shader.hpp"

namespace Phoenix
{
    class Application
    {
    public:
      /* To be defined in Client */
      static std::unique_ptr<Application> Create();

    public:
        Application();
        virtual ~Application() = default;
        
        void Run();
        
        void OnEvent(Event& e);
        
        void PushLayer(std::unique_ptr<Layer> layer);
        void PushOverlay(std::unique_ptr<Layer> layer);

        static const Window& GetWindow();
        
        ImGuiLayer& GetImGuiLayer();
        
    private:
        bool OnWindowClose(WindowCloseEvent& e);

        static std::unique_ptr<Window> m_Window;
        Layer::UniqueID m_ImGuiLayerID = 0;
        
        bool m_Running = true;
        LayerStack m_LayerStack;
        
        unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
    };
}

