#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"

#include "Core/Log.h"



std::shared_ptr<spdlog::logger> Vtt_Api::Log::api_logger;
std::shared_ptr<spdlog::logger> Vtt_Api::Log::client_logger;
std::shared_ptr<spdlog::logger> Vtt_Api::Log::server_logger;

void Vtt_Api::Log::Init() {

	// Vector holding logging sinks
	std::vector<spdlog::sink_ptr> sinks;
	spdlog::set_pattern("%^[%T] %n: %v%$");
	// Console and file logging for debug
	#ifdef DEBUG
	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	sinks.push_back(console_sink);
	#endif // DEBUG
	// File logging only for release
	auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/log.txt",
		0, 00);
	sinks.push_back(file_sink);

	api_logger = std::make_shared<spdlog::logger>("API", 
		begin(sinks), 
		end(sinks));
	api_logger->set_level(spdlog::level::info);
	api_logger->flush_on(spdlog::level::info);

	client_logger = std::make_shared<spdlog::logger>("CLIENT", 
		begin(sinks), 
		end(sinks));
	client_logger->set_level(spdlog::level::info);
	client_logger->flush_on(spdlog::level::info);

	server_logger = std::make_shared<spdlog::logger>("SERVER", 
		begin(sinks), 
		end(sinks));
}
