//
//  EntryPoint.h
//  Phoenix
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once
#include "Application.hpp"

int main()
{
    Phoenix::Logger::Init();
    
    PX_ENGINE_TRACE("Phoenix Engine!");

    Phoenix::Scope<Phoenix::Application> application = Phoenix::Application::Create();
    application->Run();
}
