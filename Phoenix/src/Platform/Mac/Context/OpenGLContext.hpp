//
//  OpenGLContext.hpp
//  Phoenix
//
//  Created by SD on 16/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Phoenix/Renderer/Interface/GraphicsContext.h"

struct GLFWwindow;

namespace Phoenix
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        virtual void Init() override;
        virtual void SwapBuffers() override;
    
    private:
        GLFWwindow* m_WindowHandle;
    };
}

