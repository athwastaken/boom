#pragma once

#include "bmpch.h"

#include "base.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace bm {
	class log {
	public:
		static void init();

		static ref<spdlog::logger>& getCoreLogger() { return s_getCoreLogger; }
		static ref<spdlog::logger>& getClientLogger() { return s_getClientLogger; }
		
	private:
		static ref<spdlog::logger> s_getCoreLogger;
		static ref<spdlog::logger> s_getClientLogger;
	};
}

// core log macros
#define BM_CORE_TRACE(...) bm::log::getCoreLogger()->trace(__VA_ARGS__)
#define BM_CORE_INFO(...) bm::log::getCoreLogger()->info(__VA_ARGS__)
#define BM_CORE_WARN(...) bm::log::getCoreLogger()->warn(__VA_ARGS__)
#define BM_CORE_ERROR(...) bm::log::getCoreLogger()->error(__VA_ARGS__)
#define BM_CORE_FATAL(...) bm::log::getCoreLogger()->fatal(__VA_ARGS__)

// client log macros
#define BM_TRACE(...) bm::log::getClientLogger()->trace(__VA_ARGS__)
#define BM_INFO(...) bm::log::getClientLogger()->info(__VA_ARGS__)
#define BM_WARN(...) bm::log::getClientLogger()->warn(__VA_ARGS__)
#define BM_ERROR(...) bm::log::getClientLogger()->error(__VA_ARGS__)
#define BM_FATAL(...) bm::log::getClientLogger()->fatal(__VA_ARGS__)