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
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
        };

        std::vector<uint32_t> sqIndices = {0, 1, 2, 2, 3, 0};
        
        m_SquareVA = VertexArray::Create();
        
        Phoenix::Ref<VertexBuffer> sqVBuffer = VertexBuffer::Create(sqVertices.data(), static_cast<uint32_t>(sqVertices.size()));
        
        Phoenix::BufferLayout sqlayout = {
            {Phoenix::ShaderDataType::Float3, "a_position"},
            {Phoenix::ShaderDataType::Float2, "a_texture"}
        };
        
        sqVBuffer->SetLayout(sqlayout);
        m_SquareVA->AddVertexBuffer(sqVBuffer);

        Phoenix::Ref<IndexBuffer>  sqIBuffer = IndexBuffer::Create(sqIndices.data(), static_cast<uint32_t>(sqIndices.size()));
        m_SquareVA->SetIndexBuffer(sqIBuffer);

        {
            std::string vertexShader = R"(
                #version 330 core
                layout(location = 0) in vec3 a_position;
                layout(location = 1) in vec2 a_texture;

                uniform mat4 u_ViewProjection;
                uniform mat4 u_Transform;
                
                out vec2 v_texCoords;
                
                void main()
                {
                   gl_Position = u_ViewProjection * u_Transform * vec4(a_position, 1.0f);
                   v_texCoords = a_texture;
                }
            )";

            std::string fragmentShader = R"(
                #version 330 core

                layout(location = 0) out vec4 color;

                in vec2 v_texCoords;

                uniform vec3 u_Color;

                void main()
                {
                   color = vec4(u_Color, 1.0f);
                }
            )";
            
            
            Phoenix::Ref<Phoenix::Shader> shader = Phoenix::Shader::Create("FlatColorShader", vertexShader, fragmentShader);
            m_ShaderLibrary.Add(shader);
        }

        Phoenix::Ref<Phoenix::Shader> texShader = m_ShaderLibrary.Load("../../Sandbox/assets/shaders/Texture.glsl");

        m_TextureCheckbox = Phoenix::Texture2D::Create("../../Sandbox/assets/textures/Checkerboard.png");
        m_TextureLogo = Phoenix::Texture2D::Create("../../Branding/PhoenixLogo.png");

        texShader->Bind();
        texShader->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(Phoenix::Timestep ts) override
    {
        Phoenix::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Phoenix::RenderCommand::Clear();
        
        auto flatColorShader = m_ShaderLibrary.Get("FlatColorShader");

        Phoenix::Renderer::BeginScene(Phoenix::Application::GetApplication().GetOrthographicCamera());
        {
            glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
            
            flatColorShader->Bind();
            flatColorShader->UploadUniformFloat3("u_Color", m_TileColor);

            for (int x = 0; x < 10; x++)
            {
                for (int y = 0; y < 10; y++)
                {
                    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.11f * x, 0.11f * y, 0)) * scaleMat;
                    Phoenix::Renderer::Submit(flatColorShader, m_SquareVA, transform);
                }
            }
            
//            Phoenix::Renderer::Submit(m_Shader, m_VertexArray);
            
            auto textureShader = m_ShaderLibrary.Get("Texture");

            m_TextureCheckbox->Bind(0);
            scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
            Phoenix::Renderer::Submit(textureShader, m_SquareVA, scaleMat);

            m_TextureLogo->Bind(0);
            scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
            Phoenix::Renderer::Submit(textureShader, m_SquareVA, scaleMat);
            
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

    Phoenix::Ref<Phoenix::VertexArray>                  m_SquareVA;
    Phoenix::Ref<Phoenix::VertexArray>                  m_VertexArray;

    Phoenix::Ref<Phoenix::Texture>                      m_TextureCheckbox;
    Phoenix::Ref<Phoenix::Texture>                      m_TextureLogo;

    Phoenix::ShaderLibrary                              m_ShaderLibrary;
    
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
