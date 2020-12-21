//
//  Timestep.h
//  Phoenix
//
//  Created by SD on 21/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

namespace Phoenix
{
    class Timestep
    {
    public:
        Timestep(float time = 0.0f) : m_Time(time) {}
        
        operator float() const { return m_Time; }
        
        float GetSeconds() const { return m_Time; }
        float GetMilliseconds() const { return m_Time * 1000; }
        
    private:
        float m_Time = 0.0f;
    };
}
