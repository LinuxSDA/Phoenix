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

#include "LayerStack.hpp"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Phoenix
{
    class Application
    {
    public:
      /* To be defined in Client */
      static std::unique_ptr<Application> Create();

    public:
        Application();
        virtual ~Application();
        
        void Run();
        
        void OnEvent(Event& e);
        
        void PushLayer(std::unique_ptr<Layer> layer);
        void PushOverlay(std::unique_ptr<Layer> layer);

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };
}


#endif /* Application_hpp */
