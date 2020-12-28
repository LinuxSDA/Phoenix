//
//  Sandbox2D.hpp
//  Sandbox
//
//  Created by SD on 27/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include <Phoenix.h>

class Sandbox2D : public Phoenix::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Phoenix::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Phoenix::Event& e) override;

private:
    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
    Phoenix::Ref<Phoenix::Texture2D> m_CheckerboardTexture;
};
