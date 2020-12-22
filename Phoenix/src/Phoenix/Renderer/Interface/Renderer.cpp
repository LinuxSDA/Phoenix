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
    Scope<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

    void Renderer::BeginScene(const Ref<const OrthographicCamera>& camera)
    {
        s_SceneData->camera = camera;
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Ref<const Shader>& shader, const Ref<const VertexArray>& va, const glm::mat4& transform)
    {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", s_SceneData->camera->GetViewProjectionMatrix());
        shader->UploadUniformMat4("u_Transform", transform);

        va->Bind();
        RenderCommand::DrawIndexed(va);
    }
}
