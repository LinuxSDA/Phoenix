//
//  GraphicsContext.h
//  Phoenix
//
//  Created by SD on 16/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

namespace Phoenix
{
    class GraphicsContext
    {
    public:
        GraphicsContext() = default;
        virtual ~GraphicsContext() = default;
        
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}
