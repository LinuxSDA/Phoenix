//
//  main.cpp
//  Sandbox
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include <px.pch>
#include <Phoenix.h>

class Sandbox : public Phoenix::Application
{
    
public:
    Sandbox(){}
    ~Sandbox(){}
};


std::unique_ptr<Phoenix::Application> Phoenix::CreateApplication()
{
    return std::make_unique<Phoenix::Application>();
}
