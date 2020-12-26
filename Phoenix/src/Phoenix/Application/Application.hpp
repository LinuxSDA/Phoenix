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
#include "OrthographicCameraController.hpp"

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
      static Scope<Application> Create();

    public:
        Application();
        virtual ~Application() = default;
        
        void Run();
                
        void PushLayer(Scope<Layer> layer);
        void PushOverlay(Scope<Layer> layer);

        const Window& GetWindow() const;
        const OrthographicCamera& GetOrthographicCamera() const;
        
        using ObserverPtr = Application*;
        inline static const Application& GetApplication() { return *m_ApplicationPointer;}

    private:
        void OnEvent(Event& e);
        bool OnWindowClose(WindowCloseEvent& e);
        ImGuiLayer& GetApplicationImGuiLayer();


    private:
        static ObserverPtr m_ApplicationPointer;
        
        Scope<Window>       m_Window;
        LayerStack          m_LayerStack;

        /* TODO: set layer ID 0 as invalid enum (instead of number) */
        uint32_t            m_CameraControllerID    = 0;
        uint32_t            m_ImGuiLayerID          = 0;
        bool                m_Running               = true;
        float               m_LastFrameTime         = 0.0f;
    };
}

