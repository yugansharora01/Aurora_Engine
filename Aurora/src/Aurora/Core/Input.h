#pragma once

#include "Aurora/Core/Keycode.h"

namespace Aurora
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsAnotherKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed();
		static bool IsRightMouseButtonPressed();
		static bool IsLeftMouseButtonPressed();
		static int GetMouseX();
		static int GetMouseY();
		static std::pair<int,int> GetMouseCoord();
	};

}