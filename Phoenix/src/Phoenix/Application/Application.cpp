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

#include "Phoenix/Renderer/Interface/Renderer.hpp"

namespace Phoenix
{
    std::unique_ptr<Window> Application::m_Window;

    Application::Application()
    {
        PX_ENGINE_ASSERT(m_Window == nullptr, "Application already exists!");
        m_Window = Window::Create();
        PX_ENGINE_ASSERT(m_Window != nullptr, "Cannnot create window!");
        m_Window->SetEventCallback(PX_BIND_EVENT_FN(Application::OnEvent));

        auto imGuiLayer = ImGuiLayer::Create();
        PX_ENGINE_ASSERT(imGuiLayer != nullptr, "Cannnot create imgui layer!");

        m_ImGuiLayerID = imGuiLayer->GetLayerID();
        PushOverlay(std::move(imGuiLayer));

        /*---------------------*/
        m_VertexArray = VertexArray::Create();
        
        std::vector<float> vertices = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        std::vector<uint32_t> indices = {0, 1, 2};

        std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices.data(), static_cast<uint32_t>(vertices.size()));

        BufferLayout layout = {
            {ShaderDataType::Float3, "position"},
            {ShaderDataType::Float4, "color"}
        };
        
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), static_cast<uint32_t>(indices.size()));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        
        std::vector<float> sqVertices = {
            -0.75f, -0.75f, 0.0f,   0.2f, 0.4f, 0.7f, 1.0f,
             0.75f, -0.75f, 0.0f,   0.2f, 0.4f, 0.7f, 1.0f,
             0.75f,  0.75f, 0.0f,   0.2f, 0.4f, 0.7f, 1.0f,
            -0.75f,  0.75f, 0.0f,   0.2f, 0.4f, 0.7f, 1.0f
        };

        std::vector<uint32_t> sqIndices = {0, 1, 2, 2, 3, 0};
        
        m_SquareVA = VertexArray::Create();
        
        std::shared_ptr<VertexBuffer> sqVBuffer = VertexBuffer::Create(sqVertices.data(), static_cast<uint32_t>(sqVertices.size()));
        
        BufferLayout sqlayout = {
            {ShaderDataType::Float3, "position"},
            {ShaderDataType::Float4, "color"}
        };
        
        sqVBuffer->SetLayout(sqlayout);
        m_SquareVA->AddVertexBuffer(sqVBuffer);

        std::shared_ptr<IndexBuffer>  sqIBuffer = IndexBuffer::Create(sqIndices.data(), static_cast<uint32_t>(sqIndices.size()));
        m_SquareVA->SetIndexBuffer(sqIBuffer);

        std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) in vec4 color;\n"
        "\n"
        "out vec3 v_position;"
        "\n"
        "out vec4 v_color;"
        "\n"
        "void main() {\n"
        "   gl_Position = vec4(position, 1.0f);\n"
        "   v_position  = position;\n"
        "   v_color     = color;\n"
        "}\n";
        

        std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "in vec3 v_position;"
        "\n"
        "in vec4 v_color;"
        "\n"
        "void main() {\n"
        "   color = v_color;\n"
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
            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            RenderCommand::Clear();
                        
            Renderer::BeginScene();
            {
                m_Shader->Bind();
                Renderer::Submit(m_SquareVA);
                Renderer::Submit(m_VertexArray);
            }
            Renderer::EndScene();

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
