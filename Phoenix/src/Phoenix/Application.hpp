//
//  Application.hpp
//  Phoenix
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Phoenix
{
    class Application
    {
      
    public:
        Application();
        virtual ~Application();
        
        void Run();
        
        void OnEvent(Event& e);
        
    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    /* To be defined in Client */
    std::unique_ptr<Application> CreateApplication();
}


#endif /* Application_hpp */
