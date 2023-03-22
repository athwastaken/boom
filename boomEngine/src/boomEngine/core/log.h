#pragma once

#include "bmpch.h"

#include "base.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace bm {
	class BM_API log {
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& coreLogger();
		inline static std::shared_ptr<spdlog::logger>& clientLogger();
		
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

// core log macros
#define BM_CORE_TRACE(...) bm::log::coreLogger()->trace(__VA_ARGS__)
#define BM_CORE_INFO(...) bm::log::coreLogger()->info(__VA_ARGS__)
#define BM_CORE_WARN(...) bm::log::coreLogger()->warn(__VA_ARGS__)
#define BM_CORE_ERROR(...) bm::log::coreLogger()->error(__VA_ARGS__)
#define BM_CORE_FATAL(...) bm::log::coreLogger()->fatal(__VA_ARGS__)

// client log macros
#define BM_TRACE(...) bm::log::clientLogger()->trace(__VA_ARGS__)
#define BM_INFO(...) bm::log::clientLogger()->info(__VA_ARGS__)
#define BM_WARN(...) bm::log::clientLogger()->warn(__VA_ARGS__)
#define BM_ERROR(...) bm::log::clientLogger()->error(__VA_ARGS__)
#define BM_FATAL(...) bm::log::clientLogger()->fatal(__VA_ARGS__)