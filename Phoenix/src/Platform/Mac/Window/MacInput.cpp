//
//  MacInput.cpp
//  Phoenix
//
//  Created by SD on 15/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "MacInput.hpp"
#include "Phoenix/Application/Application.hpp"

#include <GLFW/glfw3.h>

namespace Phoenix
{
    std::unique_ptr<Input> Input::s_Instance = std::make_unique<MacInput>();

    bool MacInput::IsKeyPressedImpl(int keycode)
    {
        const auto& window = static_cast<GLFWwindow*>(Application::GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return (state == GLFW_PRESS || state == GLFW_REPEAT);
    }


    bool MacInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> MacInput::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return { (float)xpos, (float)ypos };
    }

    float MacInput::GetMouseXImpl()
    {
        auto[x, y] = GetMousePositionImpl();
        return x;
    }

    float MacInput::GetMouseYImpl()
    {
        auto[x, y] = GetMousePositionImpl();
        return y;
    }
}
