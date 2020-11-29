//
//  MacInput.hpp
//  Phoenix
//
//  Created by SD on 15/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Phoenix/Application/Input.h"

namespace Phoenix
{
    class MacInput : public Input
    {
    public:
        static const MacInput& GetInstance();

    protected:
        virtual bool IsKeyPressedImpl(int keycode) const override;
        virtual bool IsMouseButtonPressedImpl(int button) const override;
        virtual std::pair<float, float> GetMousePositionImpl() const override;
        virtual float GetMouseXImpl() const override;
        virtual float GetMouseYImpl() const override;
    
    private:
        MacInput() {};
    };
}
