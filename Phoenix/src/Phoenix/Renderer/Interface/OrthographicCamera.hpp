//
//  OrthographicCamera.hpp
//  Phoenix
//
//  Created by SD on 20/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include <glm/glm.hpp>

namespace Phoenix
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetProjection(float left, float right, float bottom, float top);
        
        void Translate(const glm::vec3& translate);
        void Rotate(float radians);

        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
        
    private:
        void RecalculateMatrices();

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::mat4 m_TransformMatrix;
    };

}
