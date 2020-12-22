//
//  main.cpp
//  Sandbox
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include <Phoenix.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Phoenix::Layer
{
public:
    ExampleLayer(): Layer("Example")
    {
        using Phoenix::VertexArray;
        using Phoenix::VertexBuffer;
        using Phoenix::IndexBuffer;

        // Camera //
        const Phoenix::Window& window = Phoenix::Application::GetApplication().GetWindow();
        float aspectRatio = (float)(window.GetWidth()) / window.GetHeight();
        m_Camera = std::make_shared<Phoenix::OrthographicCamera>(-aspectRatio, aspectRatio, -1.0f, 1.0f);
        
        
        // Rendering //
        m_VertexArray = VertexArray::Create();
        
        std::vector<float> vertices = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        std::vector<uint32_t> indices = {0, 1, 2};

        Phoenix::Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices.data(), static_cast<uint32_t>(vertices.size()));

        Phoenix::BufferLayout layout = {
            {Phoenix::ShaderDataType::Float3, "position"},
            {Phoenix::ShaderDataType::Float4, "color"}
        };
        
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        Phoenix::Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), static_cast<uint32_t>(indices.size()));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        
        std::vector<float> sqVertices = {
            -0.5f, -0.5f, 0.0f,   0.2f, 0.4f, 0.7f, 1.0f,
             0.5f, -0.5f, 0.0f,   0.2f, 0.4f, 0.7f, 1.0f,
             0.5f,  0.5f, 0.0f,   0.2f, 0.4f, 0.7f, 1.0f,
            -0.5f,  0.5f, 0.0f,   0.2f, 0.4f, 0.7f, 1.0f
        };

        std::vector<uint32_t> sqIndices = {0, 1, 2, 2, 3, 0};
        
        m_SquareVA = VertexArray::Create();
        
        Phoenix::Ref<VertexBuffer> sqVBuffer = VertexBuffer::Create(sqVertices.data(), static_cast<uint32_t>(sqVertices.size()));
        
        Phoenix::BufferLayout sqlayout = {
            {Phoenix::ShaderDataType::Float3, "position"},
            {Phoenix::ShaderDataType::Float4, "color"}
        };
        
        sqVBuffer->SetLayout(sqlayout);
        m_SquareVA->AddVertexBuffer(sqVBuffer);

        Phoenix::Ref<IndexBuffer>  sqIBuffer = IndexBuffer::Create(sqIndices.data(), static_cast<uint32_t>(sqIndices.size()));
        m_SquareVA->SetIndexBuffer(sqIBuffer);

        std::string vertexShader = R"(
            #version 330 core
            layout(location = 0) in vec3 position;
            layout(location = 1) in vec4 color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;
            
            out vec4 v_color;
            
            void main()
            {
               gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0f);
               v_color     = color;
            }
        )";

        std::string fragmentShader = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec4 v_color;
            
            uniform vec3 u_Color;

            void main()
            {
               color = vec4(u_Color, 1.0f);
            }
        )";
        
        
        m_Shader = Phoenix::Shader::Create(vertexShader, fragmentShader);

    }

    void OnUpdate(Phoenix::Timestep ts) override
    {
        Phoenix::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Phoenix::RenderCommand::Clear();
        
        if (Phoenix::Input::IsKeyPressed(PX_KEY_LEFT))
            m_CameraPosition.x -= s_CameraMoveSpeed * ts;
        else if (Phoenix::Input::IsKeyPressed(PX_KEY_RIGHT))
            m_CameraPosition.x += s_CameraMoveSpeed * ts;

        if (Phoenix::Input::IsKeyPressed(PX_KEY_UP))
            m_CameraPosition.y += s_CameraMoveSpeed * ts;
        else if (Phoenix::Input::IsKeyPressed(PX_KEY_DOWN))
            m_CameraPosition.y -= s_CameraMoveSpeed * ts;

        if (Phoenix::Input::IsKeyPressed(PX_KEY_A))
            m_CameraRotation += s_CameraRotateSpeed * ts;
        else if (Phoenix::Input::IsKeyPressed(PX_KEY_D))
            m_CameraRotation -= s_CameraRotateSpeed * ts;

        m_Camera->SetPosition(m_CameraPosition);
        m_Camera->SetRotation(m_CameraRotation);

        Phoenix::Renderer::BeginScene(m_Camera);
        {
            glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
            
            m_Shader->UploadUniformFloat3("u_Color", m_TileColor);

            for (int x = -10; x < 10; x++)
            {
                for (int y = -10; y < 10; y++)
                {
                    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.11f * x, 0.11f * y, 0)) * scaleMat;
                    Phoenix::Renderer::Submit(m_Shader, m_SquareVA, transform);
                }
            }
            
//            Phoenix::Renderer::Submit(m_Shader, m_VertexArray);
        }
        Phoenix::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Tile Color", glm::value_ptr(m_TileColor));
        ImGui::End();
    }
    
    void OnEvent(Phoenix::Event& event) override
    {
        
    }
    

private:

    Phoenix::Ref<Phoenix::VertexArray>        m_SquareVA;
    Phoenix::Ref<Phoenix::VertexArray>        m_VertexArray;
    Phoenix::Ref<Phoenix::Shader>             m_Shader;
    Phoenix::Ref<Phoenix::OrthographicCamera> m_Camera;
    
    
    glm::vec3 m_CameraPosition{};
    glm::vec3 m_TileColor{1.0f, 1.0f, 1.0f};

    float     m_CameraRotation{};
        
    constexpr static float s_CameraMoveSpeed   = 5.0f;
    constexpr static float s_CameraRotateSpeed = 180.0f;

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


Phoenix::Scope<Phoenix::Application> Phoenix::Application::Create()
{
    return std::make_unique<Sandbox>();
}
