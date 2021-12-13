#pragma once

#include <locale>
#include <codecvt>

namespace Aurora {
	std::wstring s2ws(const std::string& str);

	std::string ws2s(const std::wstring& wstr);
}
