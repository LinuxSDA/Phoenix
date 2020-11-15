//
//  Window.h
//  Phoenix
//
//  Created by SD on 12/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//
#pragma once

#include "px.pch"

#include "Core.h"
#include "Phoenix/Events/Event.h"

namespace Phoenix
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "Phoenix Engine",
                    unsigned int width = 1280,
                    unsigned int height = 720)
            : Title(title), Width(width), Height(height)
        {
        }
    };

    // Interface representing a desktop system based Window
    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;
        
        virtual void* GetNativeWindow() const = 0;
        
        static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
    };

}
