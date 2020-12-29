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

    PX_PROFILE_BEGIN_SESSION("Phonix-Startup.json");
    Phoenix::Scope<Phoenix::Application> application = Phoenix::Application::Create();
    PX_PROFILE_END_SESSION();

    PX_PROFILE_BEGIN_SESSION("Phonix-Runtime.json");
    application->Run();
    PX_PROFILE_END_SESSION();

    PX_PROFILE_BEGIN_SESSION("Phonix-Shutdown.json");
    application.reset();
    PX_PROFILE_END_SESSION();
}
