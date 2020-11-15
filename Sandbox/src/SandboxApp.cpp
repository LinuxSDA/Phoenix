//
//  main.cpp
//  Sandbox
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include <Phoenix.h>

class ExampleLayer : public Phoenix::Layer
{
public:
    ExampleLayer(): Layer("Example")
    {
    }

    void OnUpdate() override
    {

    }

    void OnEvent(Phoenix::Event& event) override
    {

    }

};

class Sandbox : public Phoenix::Application
{
    
public:
    Sandbox()
    {
        PushLayer(std::make_unique<ExampleLayer>());
        PushOverlay(std::make_unique<Phoenix::ImGuiLayer>());
    }
    ~Sandbox(){}
};


std::unique_ptr<Phoenix::Application> Phoenix::Application::Create()
{
    return std::make_unique<Sandbox>();
}
