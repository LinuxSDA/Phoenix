//
//  Logger.hpp
//  Phoenix
//
//  Created by SD on 10/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Phoenix
{
    class Logger
    {
    public:
        static void Init();
        static std::shared_ptr<spdlog::logger> GetCoreLogger() {return sCoreLogger;}
        static std::shared_ptr<spdlog::logger> GetClientLogger() {return sClientLogger;}
    
    private:
        static std::shared_ptr<spdlog::logger> sCoreLogger;
        static std::shared_ptr<spdlog::logger> sClientLogger;
    };
}
