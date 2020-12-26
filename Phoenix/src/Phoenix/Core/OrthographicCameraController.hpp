//
//  OrthographicCameraController.hpp
//  Phoenix
//
//  Created by SD on 26/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//


#pragma once

#include "Phoenix/Renderer/Interface/OrthographicCamera.hpp"
#include "Phoenix/Events/ApplicationEvent.h"
#include "Phoenix/Events/MouseEvent.h"

#include "Layer.hpp"

namespace Phoenix
{
    /* TODO: Seperate to different file */
    /* Client can create his own Camera Controller inheriting this */
    class CameraController : public Layer
    {
    public:
        CameraController() : Layer("CameraController") {}
        ~CameraController() = default;
        
        /* TODO: In future it will return a camera base class from which prespective and orthogonal will inherit*/
        virtual OrthographicCamera& GetCamera() = 0;
        virtual const OrthographicCamera& GetCamera() const = 0;
    };

    class OrthographicCameraController : public CameraController
    {
    public:
        OrthographicCameraController(float aspectRatio);

        virtual void OnUpdate(Timestep ts) override;
        virtual void OnEvent(Event& event) override;

        virtual OrthographicCamera& GetCamera() override { return m_Camera; }
        virtual const OrthographicCamera& GetCamera() const override { return m_Camera; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

    private:
        float m_AspectRatio = 1.0f;
        float m_ZoomLevel   = 1.0f;

        OrthographicCamera m_Camera;

        float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 180.0f;
        
        float m_ZoomMaxLimit = 0.25;
        float m_ZoomMinLimit = 4;
        float m_ZoomDelta    = 0.25;
    };
}
