#include "bmpch.h"

#include "log.h"

namespace bm {
	std::shared_ptr<spdlog::logger> log::s_coreLogger;
	std::shared_ptr<spdlog::logger> log::s_clientLogger;

	void log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_coreLogger = spdlog::stdout_color_mt("Boom");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("App");
		s_clientLogger->set_level(spdlog::level::trace);

	}

	inline std::shared_ptr<spdlog::logger>& log::coreLogger()
	{
		return s_coreLogger;
	}

	inline std::shared_ptr<spdlog::logger>& log::clientLogger()
	{
		return s_clientLogger;
	}
}