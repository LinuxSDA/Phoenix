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
        if (Input::IsKeyPressed(PX_KEY_A))
            m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(PX_KEY_D))
            m_CameraPosition.x += m_CameraTranslationSpeed * ts;

        if (Input::IsKeyPressed(PX_KEY_W))
            m_CameraPosition.y += m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(PX_KEY_S))
            m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

        if (Input::IsKeyPressed(PX_KEY_Q))
            m_CameraRotation += m_CameraRotationSpeed * ts;
        else if (Input::IsKeyPressed(PX_KEY_E))
            m_CameraRotation -= m_CameraRotationSpeed * ts;

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);
    }
    
    void OrthographicCameraController::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseScrolledEvent>(PX_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(PX_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.GetYOffset() * m_ZoomDelta;
        m_ZoomLevel = std::max(m_ZoomLevel, m_ZoomMaxLimit);
        m_ZoomLevel = std::min(m_ZoomLevel, m_ZoomMinLimit);

        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        m_CameraTranslationSpeed = m_ZoomLevel;
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

}
