#pragma once

#include "bmpch.h"

#ifdef BM_DEBUG
	#define BM_ENABLE_ASSERTS
#endif

#ifdef BM_ENABLE_ASSERTS
	#define BM_ASSERT(x, ...) { if(!(x)) { BM_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BM_CORE_ASSERT(x, ...) { if(!(x)) { BM_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BM_ASSERT(x, ...)
	#define BM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BM_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace bm {
	template<typename T>
	using scope = std::unique_ptr<T>;
	template<typename T, typename ... args>
	constexpr scope<T> CreateScope(args&& ... a) {
		return std::make_unique<T>(std::forward<args>(a)...);
	}

	template<typename T>
	using ref = std::shared_ptr<T>;
	template<typename T, typename ... args>
	constexpr ref<T> CreateRef(args&& ... a) {
		return std::make_shared<T>(std::forward<args>(a)...);
	}
}

#include "boomEngine/core/log.h"