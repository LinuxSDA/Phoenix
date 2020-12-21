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

        std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices.data(), static_cast<uint32_t>(vertices.size()));

        Phoenix::BufferLayout layout = {
            {Phoenix::ShaderDataType::Float3, "position"},
            {Phoenix::ShaderDataType::Float4, "color"}
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
        
        Phoenix::BufferLayout sqlayout = {
            {Phoenix::ShaderDataType::Float3, "position"},
            {Phoenix::ShaderDataType::Float4, "color"}
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
        "uniform mat4 u_ViewProjection;"
        "\n"
        "out vec3 v_position;"
        "\n"
        "out vec4 v_color;"
        "\n"
        "void main() {\n"
        "   gl_Position = u_ViewProjection * vec4(position, 1.0f);\n"
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
        
        m_Shader = Phoenix::Shader::Create(vertexShader, fragmentShader);

    }

    void OnUpdate() override
    {
        Phoenix::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Phoenix::RenderCommand::Clear();

        if (Phoenix::Input::IsKeyPressed(PX_KEY_LEFT))
            m_CameraPosition.x -= s_CameraMoveSpeed;
        else if (Phoenix::Input::IsKeyPressed(PX_KEY_RIGHT))
            m_CameraPosition.x += s_CameraMoveSpeed;

        if (Phoenix::Input::IsKeyPressed(PX_KEY_UP))
            m_CameraPosition.y += s_CameraMoveSpeed;
        else if (Phoenix::Input::IsKeyPressed(PX_KEY_DOWN))
            m_CameraPosition.y -= s_CameraMoveSpeed;

        if (Phoenix::Input::IsKeyPressed(PX_KEY_A))
            m_CameraRotation += s_CameraRotateSpeed;
        else if (Phoenix::Input::IsKeyPressed(PX_KEY_D))
            m_CameraRotation -= s_CameraRotateSpeed;

        m_Camera->SetPosition(m_CameraPosition);
        m_Camera->SetRotation(m_CameraRotation);

        Phoenix::Renderer::BeginScene(m_Camera);
        {
            Phoenix::Renderer::Submit(m_Shader, m_SquareVA);
            Phoenix::Renderer::Submit(m_Shader, m_VertexArray);
        }
        Phoenix::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
    }
    
    void OnEvent(Phoenix::Event& event) override
    {
        
    }
    

private:

    std::shared_ptr<Phoenix::VertexArray>        m_SquareVA;
    std::shared_ptr<Phoenix::VertexArray>        m_VertexArray;
    std::shared_ptr<Phoenix::Shader>             m_Shader;
    std::shared_ptr<Phoenix::OrthographicCamera> m_Camera;
    
    
    glm::vec3 m_CameraPosition{};
    float     m_CameraRotation{};
    
    constexpr static float s_CameraMoveSpeed   = 0.1f;
    constexpr static float s_CameraRotateSpeed = 1.0f;

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
