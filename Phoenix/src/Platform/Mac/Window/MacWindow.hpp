//
//  MacWindow.hpp
//  Phoenix
//
//  Created by SD on 12/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include <GLFW/glfw3.h>

#include "Phoenix/Window.h"
#include "Phoenix/Renderer/Interface/GraphicsContext.h"

namespace Phoenix
{
    class MacWindow : public Window
    {
    public:
        MacWindow(const WindowProps& props);
        virtual ~MacWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }
        inline float        GetCurrentTime() const override { return glfwGetTime(); }
        // Window attributes
        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;
        inline virtual void * GetNativeWindow() const override {return m_Window;}
        
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow* m_Window;
        std::unique_ptr<GraphicsContext> m_Context;

        void GLFWSetEventCallbacks();
        
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };

}
