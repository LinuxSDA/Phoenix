//
//  main.cpp
//  Sandbox
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include <Phoenix.h>
#include <imgui.h>

class ExampleLayer : public Phoenix::Layer
{
public:
    ExampleLayer(): Layer("Example")
    {
    }

    void OnUpdate() override
    {
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello Test!");
        ImGui::End();
    }
    
    void OnEvent(Phoenix::Event& event) override
    {
        if(event.GetEventType() == Phoenix::EventType::KeyPressed)
            PX_TRACE("Space Pressed? : {0}" , Phoenix::Input::IsKeyPressed(PX_KEY_SPACE));
    }

};

class Sandbox : public Phoenix::Application
{
    
public:
    Sandbox()
    {
        PushLayer(std::make_unique<ExampleLayer>());
    }
    ~Sandbox(){}
};


std::unique_ptr<Phoenix::Application> Phoenix::Application::Create()
{
    return std::make_unique<Sandbox>();
}
