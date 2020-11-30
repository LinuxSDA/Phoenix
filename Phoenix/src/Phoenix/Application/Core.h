//
//  Core.h
//  Phoenix
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Logger.hpp"

/* LOGGER CORE MACROS*/
#define PX_ENGINE_TRACE(...)  ::Phoenix::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define PX_ENGINE_INFO(...)   ::Phoenix::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define PX_ENGINE_WARN(...)   ::Phoenix::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define PX_ENGINE_ERROR(...)  ::Phoenix::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define PX_ENGINE_CRITICAL(...)  ::Phoenix::Logger::GetCoreLogger()->critical(__VA_ARGS__)

/* LOGGER CLIENT MACROS*/
#define PX_TRACE(...)         ::Phoenix::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define PX_INFO(...)          ::Phoenix::Logger::GetClientLogger()->info(__VA_ARGS__)
#define PX_WARN(...)          ::Phoenix::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define PX_ERROR(...)         ::Phoenix::Logger::GetClientLogger()->error(__VA_ARGS__)
#define PX_CRITICAL(...)         ::Phoenix::Logger::GetClientLogger()->critical(__VA_ARGS__)

#ifdef DEBUG
    #define PX_ENABLE_ASSERTS 1
#endif

#if PX_ENABLE_ASSERTS
    #define PX_ASSERT(x, ...) { if(!(x)) { PX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __asm("int3"); } }
    #define PX_ENGINE_ASSERT(x, ...) { if(!(x)) { PX_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __asm("int3"); } }
#else
    #define PX_ASSERT(x, ...) {(void)(x);}
    #define PX_ENGINE_ASSERT(x, ...) {(void)(x);}
#endif

#define PX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
