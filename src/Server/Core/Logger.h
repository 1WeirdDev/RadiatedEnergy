#pragma once

#include "Core.h"

class Logger{
public:
    static void Init();
    
public:
    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
};

#define CORE_ERROR(...)	::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_WARN(...)	::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_INFO(...)	::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_TRACE(...)	::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_LOG(...)	::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_DEBUG(...)	::Logger::GetCoreLogger()->debug(__VA_ARGS__)