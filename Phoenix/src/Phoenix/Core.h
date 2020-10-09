//
//  Core.h
//  Phoenix
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#ifndef Core_h
#define Core_h


/* LOGGER CORE MACROS*/
#define PX_ENGINE_TRACE(...)  ::Phoenix::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define PX_ENGINE_INFO(...)   ::Phoenix::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define PX_ENGINE_WARN(...)   ::Phoenix::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define PX_ENGINE_ERROR(...)  ::Phoenix::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define PX_ENGINE_FATAL(...)  ::Phoenix::Logger::GetCoreLogger()->fatal(__VA_ARGS__)

/* LOGGER CLIENT MACROS*/
#define PX_TRACE(...)         ::Phoenix::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define PX_INFO(...)          ::Phoenix::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define PX_WARN(...)          ::Phoenix::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define PX_ERROR(...)         ::Phoenix::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define PX_FATAL(...)         ::Phoenix::Logger::GetCoreLogger()->fatal(__VA_ARGS__)

#endif /* Core_h */
