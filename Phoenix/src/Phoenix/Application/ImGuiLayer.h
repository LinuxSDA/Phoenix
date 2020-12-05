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

/* Platform specific, created in Platform/<Mac/Win>*/

namespace Phoenix
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer() : Layer("ImGuiLayer"){}
        ~ImGuiLayer() = default;
        
        virtual void Begin() = 0;
        virtual void End() = 0;
        
        static std::unique_ptr<ImGuiLayer> Create();
    };
}
