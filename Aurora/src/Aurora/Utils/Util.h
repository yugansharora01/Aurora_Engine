#pragma once
#include "Platform/Windows/Utility.h"

namespace Aurora {
	template<typename ...Args>
	std::vector<int> GetDisplayCoord(Args... args)
	{
		if (AU_PLATFORM_WINDOWS)
		{
			return WinGetDisplayCoord(args...);
		}
	}
}