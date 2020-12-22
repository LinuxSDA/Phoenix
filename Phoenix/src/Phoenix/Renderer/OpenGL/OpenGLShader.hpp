//
//  Header.h
//  Phoenix
//
//  Created by SD on 29/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Phoenix/Renderer/Interface/Shader.hpp"

namespace Phoenix
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;
    
        virtual void UploadUniformInt(const std::string& name, int value) const override;

        virtual void UploadUniformFloat(const std::string& name, float value) const override;
        virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value) const override;
        virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value) const override;
        virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value) const override;

        virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const override;
        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;

    private:
        uint32_t m_RendererID = 0;
    };
}
