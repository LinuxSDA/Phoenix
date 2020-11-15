//
//  ImGuiLayer.hpp
//  Phoenix
//
//  Created by SD on 14/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Phoenix/Application/Layer.hpp"

#include "Phoenix/Events/KeyEvent.h"
#include "Phoenix/Events/MouseEvent.h"
#include "Phoenix/Events/ApplicationEvent.h"

namespace Phoenix
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);
    
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);
        
    private:
        float m_Time = 0.0f;
    };
}
