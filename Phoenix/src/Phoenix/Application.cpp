//
//  Application.cpp
//  Phoenix
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"

#include "Application.hpp"
#include "Events/ApplicationEvent.h"
#include "Logger.hpp"

namespace Phoenix
{
    Application::Application() {}
    Application::~Application() {}
    
    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);
        
        if (e.IsInCategory(EventCategoryApplication))
        {
            PX_ENGINE_TRACE(e);
        }
        if (e.IsInCategory(EventCategoryInput))
        {
            PX_ENGINE_TRACE(e);
        }

        
        while (true);
    }
}
