//
//  Application.hpp
//  Phoenix
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <memory>

namespace Phoenix
{
    class Application
    {
      
    public:
        Application();
        virtual ~Application();
        
        void Run();
    };

    /* To be defined in Client */
    std::unique_ptr<Application> CreateApplication();
}


#endif /* Application_hpp */
