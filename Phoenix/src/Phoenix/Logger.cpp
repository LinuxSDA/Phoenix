//
//  Logger.cpp
//  Phoenix
//
//  Created by SD on 10/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "Logger.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Phoenix
{
    std::shared_ptr<spdlog::logger> Logger::sCoreLogger;
    std::shared_ptr<spdlog::logger> Logger::sClientLogger;

    void Logger::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        sCoreLogger = spdlog::stdout_color_mt("Core");
        sCoreLogger->set_level(spdlog::level::trace);

        sClientLogger = spdlog::stdout_color_mt("Client");
        sClientLogger->set_level(spdlog::level::trace);
    }
}
