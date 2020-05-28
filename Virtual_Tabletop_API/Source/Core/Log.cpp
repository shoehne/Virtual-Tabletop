#include <VTT_API_PCH.h>
#include "spdlog/sinks/stdout_color_sinks.h"

#include <Core/Log.h>

namespace Virtual_TT_API {

	std::shared_ptr<spdlog::logger> Log::client_logger;
	std::shared_ptr<spdlog::logger> Log::server_logger;

	void Log::Init() {

		spdlog::set_pattern("%^[%Y/%m/%d %T] %n: %v%$");
		client_logger = spdlog::stdout_color_mt("CLIENT");
		client_logger->set_level(spdlog::level::trace);

		server_logger = spdlog::stdout_color_mt("SERVER");
		server_logger->set_level(spdlog::level::trace);
	}
}