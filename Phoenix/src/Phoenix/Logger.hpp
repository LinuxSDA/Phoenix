//
//  Logger.hpp
//  Phoenix
//
//  Created by SD on 10/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#ifndef Logger_hpp
#define Logger_hpp

#include "spdlog/spdlog.h"
#include "Core.h"

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

#endif /* Logger_hpp */
