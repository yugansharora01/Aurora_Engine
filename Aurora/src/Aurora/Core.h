#pragma once

#ifdef AU_PLATFORM_WINDOWS
#if AU_DYNAMIC_LINK
	#ifdef AU_BUILD_DLL
		#define AURORA_API __declspec(dllexport)
	#else
		#define AURORA_API __declspec(dllimport)
	#endif // AU_BUILD_DLL
#else 
#define AURORA_API
#endif
#else
	#error Aurora only supports windows

#endif // AU_PLATFORM_WINDOWS

#ifdef AU_ENABLE_ASSERTS
	#define AU_ASSERT(x,...) {if(!(x)){ AU_ERROR("Assertion failed {0}",__VA_ARGS__);__debugbreak(); }}
	#define AU_CORE_ASSERT(x,...) {if(!(x)){ AU_CORE_ERROR("Assertion failed {0}",__VA_ARGS__);__debugbreak(); }}
#else
	#define AU_ASSERT(x,...) 
	#define AU_CORE_ASSERT(x,...) 
#endif

#define BIT(x) (1 << x)

#define AURORA_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#ifdef AU_DEBUG
	#define AU_DEBUGNOEXCEPT noexcept
#else
	#define DEBUGNOEXCEPT 
#endif