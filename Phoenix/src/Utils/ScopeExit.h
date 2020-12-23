//
//  ScopeExit.h
//  Phoenix
//
//  Created by SD on 23/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "px.pch"

namespace Phoenix
{
    class ScopeExit
    {
    public:
        ScopeExit(std::function<void()> destructor) : m_Destructor(destructor)
        {
            
        }
        
        ~ScopeExit()
        {
            m_Destructor();
        }
        
    private:
        std::function<void()> m_Destructor;
    };

    #define AT_SCOPE_EXIT(x) ScopeExit Phoenix_ScopeExit_exit([&]()x)
}

