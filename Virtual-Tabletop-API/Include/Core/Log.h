#pragma once
#ifndef LOG_H
#define LOG_H

/*<------spdlog------>*/
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

/*<------VTT_API------>*/
#include <Core/Core.h>

namespace Virtual_Tt_Api {

	class Log {

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetApiLogger() { return api_logger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return client_logger; }
		inline static std::shared_ptr<spdlog::logger>& GetServerLogger() { return server_logger; }

	private:
		static std::shared_ptr<spdlog::logger> api_logger;
		static std::shared_ptr<spdlog::logger> client_logger;
		static std::shared_ptr<spdlog::logger> server_logger;
	};
}

// General log macros
#define VTT_API_TRACE(...)			::Virtual_Tt_Api::Log::GetApiLogger()->trace(__VA_ARGS__)
#define VTT_API_INFO(...)			::Virtual_Tt_Api::Log::GetApiLogger()->info(__VA_ARGS__)
#define VTT_API_WARN(...)			::Virtual_Tt_Api::Log::GetApiLogger()->warn(__VA_ARGS__)
#define VTT_API_ERROR(...)			::Virtual_Tt_Api::Log::GetApiLogger()->error(__VA_ARGS__)
#define VTT_API_FATAL(...)			::Virtual_Tt_Api::Log::GetApiLogger()->fatal(__VA_ARGS__)

// Client specific log macros
#define VTT_CLIENT_TRACE(...)		::Virtual_Tt_Api::Log::GetClientLogger()->error(__VA_ARGS__)
#define VTT_CLIENT_INFO(...)		::Virtual_Tt_Api::Log::GetClientLogger()->info(__VA_ARGS__)
#define VTT_CLIENT_WARN(...)		::Virtual_Tt_Api::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VTT_CLIENT_ERROR(...)		::Virtual_Tt_Api::Log::GetClientLogger()->error(__VA_ARGS__)
#define VTT_CLIENT_FATAL(...)		::Virtual_Tt_Api::Log::GetClientLogger()->fatal(__VA_ARGS__)

// Server specific log macros
#define VTT_SERVER_TRACE(...)		::Virtual_Tt_Api::Log::GetServerLogger()->trace(__VA_ARGS__)
#define VTT_SERVER_INFO(...)		::Virtual_Tt_Api::Log::GetServerLogger()->info(__VA_ARGS__)
#define VTT_SERVER_WARN(...)		::Virtual_Tt_Api::Log::GetServerLogger()->warn(__VA_ARGS__)
#define VTT_SERVER_ERROR(...)		::Virtual_Tt_Api::Log::GetServerLogger()->error(__VA_ARGS__)
#define VTT_SERVER_FATAL(...)		::Virtual_Tt_Api::Log::GetServerLogger()->fatal(__VA_ARGS__)

#endif
