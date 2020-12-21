//
//  Shader.hpp
//  Phoenix
//
//  Created by SD on 29/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include <glm/matrix.hpp>

namespace Phoenix
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void UploadUniformMat4(const std::string&, const glm::mat4&) const = 0;

        static std::unique_ptr<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}
