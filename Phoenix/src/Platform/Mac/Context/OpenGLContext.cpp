//
//  OpenGLContext.cpp
//  Phoenix
//
//  Created by SD on 16/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "OpenGLContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Phoenix
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle):m_WindowHandle(windowHandle)
    {
        PX_ENGINE_ASSERT(m_WindowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init()
    {
        PX_PROFILE_FUNCTION();
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        PX_ENGINE_ASSERT(status, "Failed to load glad!");
    }

    void OpenGLContext::SwapBuffers()
    {
        PX_PROFILE_FUNCTION();
        glfwSwapBuffers(m_WindowHandle);
    }
}
