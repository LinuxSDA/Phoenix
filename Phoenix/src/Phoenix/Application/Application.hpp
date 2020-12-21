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
#include "Phoenix/Renderer/Interface/Shader.hpp"
#include "Phoenix/Renderer/Interface/Buffer.hpp"
#include "Phoenix/Renderer/Interface/VertexArray.hpp"
#include "Phoenix/Renderer/Interface/OrthographicCamera.hpp"

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
                
        void PushLayer(std::unique_ptr<Layer> layer);
        void PushOverlay(std::unique_ptr<Layer> layer);

        const Window& GetWindow() const;
                
        using ObserverPtr = Application*;
        inline static const Application& GetApplication() { return *m_ApplicationPointer;}

    private:
        void OnEvent(Event& e);
        bool OnWindowClose(WindowCloseEvent& e);
        ImGuiLayer& GetApplicationImGuiLayer();


    private:
        static ObserverPtr m_ApplicationPointer;
        
        std::unique_ptr<Window> m_Window;
        Layer::UniqueID m_ImGuiLayerID = 0;
        bool m_Running = true;
        float m_LastFrameTime = 0.0f;
        LayerStack m_LayerStack;
    };
}

