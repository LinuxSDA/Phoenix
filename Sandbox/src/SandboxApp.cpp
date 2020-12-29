//
//  main.cpp
//  Sandbox
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include <Phoenix.h>
#include <Phoenix/Core/EntryPoint.h>

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.hpp"

class Sandbox : public Phoenix::Application
{
    
public:
    Sandbox()
    {
        PX_PROFILE_FUNCTION();

        PushLayer(Phoenix::CreateScope<Sandbox2D>());
    }
    ~Sandbox(){}
};

Phoenix::Scope<Phoenix::Application> Phoenix::Application::Create()
{
    PX_PROFILE_FUNCTION();

    return Phoenix::CreateScope<Sandbox>();
}
