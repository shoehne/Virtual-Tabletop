#pragma once
#ifndef LOG_H
#define LOG_H

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "Core/Core.h"

namespace Vtt_Api {

	class Log {

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetApiLogger() { return api_logger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return client_logger; }
		inline static std::shared_ptr<spdlog::logger>& GetServerLogger() { return server_logger; }

	private:
		// Different loggers for API, Client and Server
		static std::shared_ptr<spdlog::logger> api_logger;
		static std::shared_ptr<spdlog::logger> client_logger;
		static std::shared_ptr<spdlog::logger> server_logger;
	};
}

#define VTT_API_INFO(...)									::Vtt_Api::Log::GetApiLogger()->info(__VA_ARGS__)
#define VTT_API_WARN(...)									::Vtt_Api::Log::GetApiLogger()->warn(__VA_ARGS__)
#define VTT_API_ERROR(...)									::Vtt_Api::Log::GetApiLogger()->error(__VA_ARGS__)

#define VTT_CLIENT_INFO(...)								::Vtt_Api::Log::GetClientLogger()->info(__VA_ARGS__)
#define VTT_CLIENT_WARN(...)								::Vtt_Api::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VTT_CLIENT_ERROR(...)								::Vtt_Api::Log::GetClientLogger()->error(__VA_ARGS__)

#define VTT_SERVER_INFO(...)								::Vtt_Api::Log::GetServerLogger()->info(__VA_ARGS__)
#define VTT_SERVER_WARN(...)								::Vtt_Api::Log::GetServerLogger()->warn(__VA_ARGS__)
#define VTT_SERVER_ERROR(...)								::Vtt_Api::Log::GetServerLogger()->error(__VA_ARGS__)
#endif
