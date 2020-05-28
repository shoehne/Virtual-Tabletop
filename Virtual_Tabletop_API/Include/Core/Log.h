#pragma once

/*<------spdlog------>*/
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

/*<------VTT_API------>*/
#include <Core/Core.h>

namespace Virtual_TT_API {

	class VTT_API Log {

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return client_logger; }
		inline static std::shared_ptr<spdlog::logger>& GetServerLogger() { return server_logger; }

	private:
		static std::shared_ptr<spdlog::logger> client_logger;
		static std::shared_ptr<spdlog::logger> server_logger;
	};
}

// Client log macros
#define VTT_CLIENT_TRACE(...)	::Virtual_TT_API::Log::GetClientLogger()->error(__VA_ARGS__)
#define VTT_CLIENT_INFO(...)	::Virtual_TT_API::Log::GetClientLogger()->error(__VA_ARGS__)
#define VTT_CLIENT_WARN(...)	::Virtual_TT_API::Log::GetClientLogger()->error(__VA_ARGS__)
#define VTT_CLIENT_ERROR(...)	::Virtual_TT_API::Log::GetClientLogger()->error(__VA_ARGS__)
#define VTT_CLIENT_FATAL(...)	::Virtual_TT_API::Log::GetClientLogger()->fatal(__VA_ARGS__)

// Server log macros
#define VTT_SERVER_TRACE(...)	::Virtual_TT_API::Log::GetServerLogger()->error(__VA_ARGS__)
#define VTT_SERVER_INFO(...)	::Virtual_TT_API::Log::GetServerLogger()->error(__VA_ARGS__)
#define VTT_SERVER_WARN(...)	::Virtual_TT_API::Log::GetServerLogger()->error(__VA_ARGS__)
#define VTT_SERVER_ERROR(...)	::Virtual_TT_API::Log::GetServerLogger()->error(__VA_ARGS__)
#define VTT_SERVER_FATAL(...)	::Virtual_TT_API::Log::GetServerLogger()->fatal(__VA_ARGS__)


