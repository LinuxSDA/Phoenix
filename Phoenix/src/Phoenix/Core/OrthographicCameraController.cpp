//
//  OrthographicCameraController.cpp
//  Phoenix
//
//  Created by SD on 26/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "OrthographicCameraController.hpp"
#include "Input.h"
#include "KeyCodes.h"

namespace Phoenix
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio) :
                                  m_AspectRatio(aspectRatio),
                                  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
                                  m_CameraTranslationSpeed(m_ZoomLevel)
    {
        
    }

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        PX_PROFILE_FUNCTION();

        if (Input::IsKeyPressed(PX_KEY_A))
            m_Camera.Translate(glm::vec3{-m_CameraTranslationSpeed * ts, 0, 0});
        else if (Input::IsKeyPressed(PX_KEY_D))
            m_Camera.Translate(glm::vec3{m_CameraTranslationSpeed * ts, 0, 0});

        if (Input::IsKeyPressed(PX_KEY_W))
            m_Camera.Translate(glm::vec3{0, m_CameraTranslationSpeed * ts, 0});
        else if (Input::IsKeyPressed(PX_KEY_S))
            m_Camera.Translate(glm::vec3{0, -m_CameraTranslationSpeed * ts, 0});

        if (Input::IsKeyPressed(PX_KEY_Q))
            m_Camera.Rotate(m_CameraRotationSpeed * ts);
        else if (Input::IsKeyPressed(PX_KEY_E))
            m_Camera.Rotate(-m_CameraRotationSpeed * ts);
    }
    
    void OrthographicCameraController::OnEvent(Event& event)
    {
        PX_PROFILE_FUNCTION();

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseScrolledEvent>(PX_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(PX_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        PX_PROFILE_FUNCTION();

        m_ZoomLevel -= e.GetYOffset() * m_ZoomDelta;
        m_ZoomLevel = std::max(m_ZoomLevel, m_ZoomMaxLimit);
        m_ZoomLevel = std::min(m_ZoomLevel, m_ZoomMinLimit);

        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        m_CameraTranslationSpeed = m_ZoomLevel;
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        PX_PROFILE_FUNCTION();

        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

}
