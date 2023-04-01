#include "bmpch.h"
#include "log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace bm {
	ref<spdlog::logger> log::s_coreLogger;
	ref<spdlog::logger> log::s_clientLogger;

	void log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_coreLogger = spdlog::stdout_color_mt("Boom");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("App");
		s_clientLogger->set_level(spdlog::level::trace);
	}
}