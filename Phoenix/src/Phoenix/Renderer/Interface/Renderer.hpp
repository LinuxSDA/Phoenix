//
//  Renderer.hpp
//  Phoenix
//
//  Created by SD on 29/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "RenderCommand.hpp"
#include "Shader.hpp"
#include "OrthographicCamera.hpp"

namespace Phoenix
{
    class Renderer
    {
    public:
        Renderer() = delete;
        
        static void BeginScene(const std::shared_ptr<const OrthographicCamera>& camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<const Shader>& shader, const std::shared_ptr<const VertexArray>& va, const glm::mat4& transform = glm::mat4(1.0f));
        
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
        
    private:
        struct SceneData
        {
            std::shared_ptr<const OrthographicCamera> camera;
        };
        
        static std::unique_ptr<SceneData> s_SceneData;
    };
}
