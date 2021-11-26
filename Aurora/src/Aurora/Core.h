#pragma once

#include <memory>

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

#ifdef AU_RELEASE
#define AU_RELEASENOEXCEPT noexcept
#else
#define AU_RELEASENOEXCEPT 
#endif

#ifdef AU_DEBUG
#define AU_DEBUGNOEXCEPT noexcept
#else
#define AU_DEBUGNOEXCEPT 
#endif


namespace Aurora {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T,typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args) 
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T,typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}