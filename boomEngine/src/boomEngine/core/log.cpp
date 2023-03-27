#include "bmpch.h"

#include "log.h"

namespace bm {
	std::shared_ptr<spdlog::logger> log::s_getCoreLogger;
	std::shared_ptr<spdlog::logger> log::s_getClientLogger;

	void log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_getCoreLogger = spdlog::stdout_color_mt("Boom");
		s_getCoreLogger->set_level(spdlog::level::trace);

		s_getClientLogger = spdlog::stdout_color_mt("App");
		s_getClientLogger->set_level(spdlog::level::trace);
	}
}