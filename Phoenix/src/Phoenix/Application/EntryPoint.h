//
//  EntryPoint.h
//  Phoenix
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#ifndef EntryPoint_h
#define EntryPoint_h

#include "Application.hpp"

int main()
{
    Phoenix::Logger::Init();
    
    PX_ENGINE_TRACE("Phoenix Engine!");

    std::unique_ptr<Phoenix::Application> application = Phoenix::Application::Create();
    application->Run();
}
#endif /* EntryPoint_h */
