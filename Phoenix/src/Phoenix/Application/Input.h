//
//  Input.h
//  Phoenix
//
//  Created by SD on 15/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Core.h"

namespace Phoenix
{
    class Input
    {
    public:
        inline static bool IsKeyPressed(int keycode) {return GetInstance().IsKeyPressedImpl(keycode);}
        inline static bool IsMouseButtonPressed(int button) { return GetInstance().IsMouseButtonPressedImpl(button); }
        inline static std::pair<float, float> GetMousePosition() { return GetInstance().GetMousePositionImpl(); }
        inline static float GetMouseX() { return GetInstance().GetMouseXImpl(); }
        inline static float GetMouseY() { return GetInstance().GetMouseYImpl(); }

        virtual ~Input(){}

    protected:
        virtual bool IsKeyPressedImpl(int keycode) const = 0;
        virtual bool IsMouseButtonPressedImpl(int button) const = 0;
        virtual std::pair<float, float> GetMousePositionImpl() const = 0;
        virtual float GetMouseXImpl() const = 0;
        virtual float GetMouseYImpl() const = 0;

    private:
        static const Input& GetInstance();
    };
}
