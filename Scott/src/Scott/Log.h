#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Scott
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


// Core Log Macros
#define SC_CORE_TRACE(...)	::Scott::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define SC_CORE_INFO(...)	::Scott::Log::GetCoreLogger()->info(__VA_ARGS__);
#define SC_CORE_WARN(...)	::Scott::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define SC_CORE_ERROR(...)	::Scott::Log::GetCoreLogger()->error(__VA_ARGS__);
#define SC_CORE_FATAL(...)	::Scott::Log::GetCoreLogger()->fatal(__VA_ARGS__);

// Client Log Macros
#define SC_TRACE(...)		::Scott::Log::GetClientLogger()->trace(__VA_ARGS__);
#define SC_INFO(...)		::Scott::Log::GetClientLogger()->info(__VA_ARGS__);
#define SC_WARN(...)		::Scott::Log::GetClientLogger()->warn(__VA_ARGS__);
#define SC_ERROR(...)		::Scott::Log::GetClientLogger()->error(__VA_ARGS__);
#define SC_FATAL(...)		::Scott::Log::GetClientLogger()->fatal(__VA_ARGS__);
