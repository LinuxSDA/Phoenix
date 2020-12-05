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

        virtual void Bind() const;
        virtual void Unbind() const;
    
    private:
        uint32_t m_RendererID = 0;
    };
}
