//
//  Renderer.cpp
//  Phoenix
//
//  Created by SD on 29/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "Renderer.hpp"

namespace Phoenix
{
    std::unique_ptr<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

    void Renderer::BeginScene(const std::shared_ptr<const OrthographicCamera>& camera)
    {
        s_SceneData->camera = camera;
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<const Shader>& shader, const std::shared_ptr<const VertexArray>& va)
    {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", s_SceneData->camera->GetViewProjectionMatrix());

        va->Bind();
        RenderCommand::DrawIndexed(va);
    }
}
