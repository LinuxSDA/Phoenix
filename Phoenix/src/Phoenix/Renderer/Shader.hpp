//
//  Shader.hpp
//  Phoenix
//
//  Created by SD on 29/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

namespace Phoenix
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;
    private:
        uint32_t m_RendererID;
    };
}
