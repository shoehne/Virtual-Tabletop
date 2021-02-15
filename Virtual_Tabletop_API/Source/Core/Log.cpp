#include <VttApiPch.h>
#include "spdlog/sinks/stdout_color_sinks.h"

#include <Core/Log.h>

namespace Virtual_Tt_Api {

	std::shared_ptr<spdlog::logger> Log::api_logger;
	std::shared_ptr<spdlog::logger> Log::client_logger;
	std::shared_ptr<spdlog::logger> Log::server_logger;

	void Log::Init() {

		spdlog::set_pattern("%^[%Y/%m/%d %T] %n: %v%$");
		api_logger = spdlog::stdout_color_mt("API");
		api_logger->set_level(spdlog::level::trace);

		client_logger = spdlog::stdout_color_mt("CLIENT");
		client_logger->set_level(spdlog::level::trace);

		server_logger = spdlog::stdout_color_mt("SERVER");
		server_logger->set_level(spdlog::level::trace);
	}
}