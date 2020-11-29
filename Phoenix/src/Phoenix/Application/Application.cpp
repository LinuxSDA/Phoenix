//
//  Application.cpp
//  Phoenix
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"

#include "Application.hpp"
#include "Logger.hpp"
#include "Input.h"

#include <glad/glad.h>

namespace Phoenix
{
    std::unique_ptr<Window> Application::m_Window;

    Application::Application()
    {
        PX_ENGINE_ASSERT(m_Window == nullptr, "Application already exists!");
        m_Window = Window::Create();
        PX_ENGINE_ASSERT(m_Window != nullptr, "Cannnot create window!");
        m_Window->SetEventCallback(PX_BIND_EVENT_FN(Application::OnEvent));

        PX_ENGINE_TRACE("GL Version: ", glGetString(GL_VERSION));

        auto imGuiLayer = ImGuiLayer::Create();
        PX_ENGINE_ASSERT(imGuiLayer != nullptr, "Cannnot create imgui layer!");

        m_ImGuiLayerID = imGuiLayer->GetLayerID();
        PushOverlay(std::move(imGuiLayer));

        /*---------------------*/
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);
        
        std::vector<float> vertices = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        std::vector<uint32_t> indices = {0, 1, 2};

        m_VertexBuffer = VertexBuffer::Create(vertices.data(), static_cast<uint32_t>(vertices.size() * sizeof(vertices[0])));
        m_IndexBuffer = IndexBuffer::Create(indices.data(), static_cast<uint32_t>(indices.size()));
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
                
        
        std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main() {\n"
        "   gl_Position = position;\n"
        "}\n";
        

        std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main() {\n"
        "   color = vec4(0.0, 1.0, 0.0, 1.0);\n"
        "}\n";
        
        m_Shader = Shader::Create(vertexShader, fragmentShader);
    }

    const Window& Application::GetWindow()
    {
        PX_ENGINE_ASSERT(m_Window != nullptr, "Window not intialized!");
        return *m_Window;
    }

    void Application::PushLayer(std::unique_ptr<Layer> layer)
    {
        m_LayerStack.PushLayer(std::move(layer));
    }

    void Application::PushOverlay(std::unique_ptr<Layer> layer)
    {
        m_LayerStack.PushOverlay(std::move(layer));
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatch(e);
        
        dispatch.Dispatch<WindowCloseEvent>(PX_BIND_EVENT_FN(Application::OnWindowClose));
        
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin() && !e.m_Handled; )
        {
            (*--it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    ImGuiLayer& Application::GetImGuiLayer()
    {
        auto imGuiLayerOptional = m_LayerStack.Get(m_ImGuiLayerID);
        PX_ENGINE_ASSERT(imGuiLayerOptional, "ImGui Layer doesn't exist!");

        ImGuiLayer& imGuiLayer = static_cast<ImGuiLayer&>(imGuiLayerOptional->get());
        
        return imGuiLayer;
    }

    void Application::Run()
    {
        auto& appImGuiLayer = GetImGuiLayer();

        while (m_Running)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);
                        
            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
            
            for (auto& layer : m_LayerStack)
                layer->OnUpdate();

            appImGuiLayer.Begin();
            
            for (auto& layer : m_LayerStack)
                layer->OnImGuiRender();

            appImGuiLayer.End();
            
            m_Window->OnUpdate();
        }
    }
}
