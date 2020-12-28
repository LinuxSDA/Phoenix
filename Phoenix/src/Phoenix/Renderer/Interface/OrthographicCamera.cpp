//
//  OrthographicCamera.cpp
//  Phoenix
//
//  Created by SD on 20/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "OrthographicCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Phoenix
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : m_ViewMatrix(1.0f), m_TransformMatrix(1.0f)
    {
        SetProjection(left, right, bottom, top);
    }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        RecalculateMatrices();
    }

    void OrthographicCamera::Translate(const glm::vec3& translate)
    {
        m_TransformMatrix = glm::translate(m_TransformMatrix, translate);
        RecalculateMatrices();
    }

    void OrthographicCamera::Rotate(float radians)
    {
        m_TransformMatrix = glm::rotate(m_TransformMatrix, radians, glm::vec3(0, 0, 1));
        RecalculateMatrices();
    }

    void OrthographicCamera::RecalculateMatrices()
    {
        m_ViewMatrix = glm::inverse(m_TransformMatrix);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}
