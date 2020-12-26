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
        
        static void Init();
        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const Ref<const Shader>& shader, const Ref<const VertexArray>& va, const glm::mat4& transform = glm::mat4(1.0f));
        
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
        
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };
        
        static Scope<SceneData> s_SceneData;
    };
}
