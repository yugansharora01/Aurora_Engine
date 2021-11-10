#include "pch.h"
#include "Utility.h"

#include "Aurora/Application.h"
#include "Aurora/Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Aurora {
	std::vector<int> WinGetDisplayCoord()
	{
		auto wnd = (Win32_Window*)Application::Get().GetWindow().GetNativeWindowPtr();
		HWND hwnd = wnd->GetHandle();


		RECT rect;

		GetWindowRect(hwnd, &rect);

		RECT wrect;
		GetWindowRect(hwnd, &wrect);
		RECT crect;
		GetClientRect(hwnd, &crect);
		POINT lefttop = { crect.left, crect.top }; // Practicaly both are 0
		ClientToScreen(hwnd, &lefttop);
		POINT rightbottom = { crect.right, crect.bottom };
		ClientToScreen(hwnd, &rightbottom);

		int left_border = lefttop.x - wrect.left; // Windows 10: includes transparent part
		int right_border = wrect.right - rightbottom.x; // As above
		int bottom_border = wrect.bottom - rightbottom.y; // As above
		int top_border_with_title_bar = lefttop.y - wrect.top; // There is no transparent part

		std::vector<int> vec = { rect.left + left_border, rect.top + top_border_with_title_bar ,rect.right - right_border ,rect.bottom - bottom_border };
		return vec;

	}
}