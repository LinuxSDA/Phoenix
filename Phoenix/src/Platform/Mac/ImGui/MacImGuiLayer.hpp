//
//  MacImGuiLayer.hpp
//  Phoenix
//
//  Created by SD on 16/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Phoenix/Application/ImGuiLayer.h"

namespace Phoenix
{
    class MacImGuiLayer : public ImGuiLayer
    {
    public:
        MacImGuiLayer();
        ~MacImGuiLayer();
        
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void Begin() override;
        virtual void End() override;
        virtual void OnImGuiRender() override;
    };
}
