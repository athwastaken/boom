#pragma once

#include "bmpch.h"

#ifdef BM_PLATFORM_WINDOWS
	#ifdef BM_BUILD_DLL
		#define BM_API __declspec(dllexport)
	#else
		#define BM_API __declspec(dllimport)
	#endif
#else
	#error Boom only supports Windows at this time.
#endif

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