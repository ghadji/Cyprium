#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Cyprium
{
	class CYPRIUM_API Log
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


// Core Log macros
#define CP_CORE_TRACE(...)    ::Cyprium::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CP_CORE_INFO(...)     ::Cyprium::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CP_CORE_WARN(...)     ::Cyprium::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CP_CORE_ERROR(...)    ::Cyprium::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CP_CORE_FATAL(...)    ::Cyprium::Log::GetCoreLogger()->fatal(__VA_ARGS__)
												  
// Client Log macros
#define CP_TRACE(...)		  ::Cyprium::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CP_INFO(...)		  ::Cyprium::Log::GetClientLogger()->info(__VA_ARGS__)
#define CP_WARN(...)		  ::Cyprium::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CP_FATAL(...)		  ::Cyprium::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define CP_ERROR(...)		  ::Cyprium::Log::GetClientLogger()->error(__VA_ARGS__)