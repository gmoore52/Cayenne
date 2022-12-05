//
// Created by gavin on 12/4/2022.
//
#include "core.h"
#include "../lib/spdlog/include/spdlog/spdlog.h"
#include "../lib/spdlog/include/spdlog/sinks/stdout_color_sinks.h"
#include "../lib/spdlog/include/spdlog/fmt/ostr.h"

#ifndef CAYENNE_LOG_H
#define CAYENNE_LOG_H

namespace Cayenne {

    class CY_API Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
        private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

} // Cayenne

#define CY_CORE_TRACE(...)   ::Cayenne::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CY_CORE_INFO(...)    ::Cayenne::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CY_CORE_WARN(...)    ::Cayenne::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CY_CORE_ERROR(...)   ::Cayenne::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CY_CORE_CRIT(...)    ::Cayenne::Log::GetCoreLogger()->critical(__VA_ARGS__)


#define CY_TRACE(...)   ::Cayenne::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CY_INFO(...)    ::Cayenne::Log::GetClientLogger()->info(__VA_ARGS__)
#define CY_WARN(...)    ::Cayenne::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CY_ERROR(...)   ::Cayenne::Log::GetClientLogger()->error(__VA_ARGS__)
#define CY_CRIT(...)    ::Cayenne::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif //CAYENNE_LOG_H
