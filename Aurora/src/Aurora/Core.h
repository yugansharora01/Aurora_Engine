#pragma once

#ifdef AU_PLATFORM_WINDOWS
	#ifdef AU_BUILD_DLL
		#define AURORA_API __declspec(dllexport)
	#else
		#define AURORA_API __declspec(dllimport)
	#endif // AU_BUILD_DLL
#else
	#error Aurora only supports windows

#endif // AU_PLATFORM_WINDOWS

#define BIT(x) (1 << x)
