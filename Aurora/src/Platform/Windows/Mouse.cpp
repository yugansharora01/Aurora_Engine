#include "pch.h"
#include "AuroraWin.h"
#include "Mouse.h"

namespace Aurora {

	std::pair<int, int> Mouse::GetPos() const noexcept
	{
		return { x, y };
	}

	int Mouse::GetPosX() const noexcept
	{
		return x;
	}

	int Mouse::GetPosY() const noexcept
	{
		return y;
	}

	bool Mouse::IsInWindow() const noexcept
	{
		return isInWindow;
	}

	bool Mouse::IsLeftPressed() const noexcept
	{
		return leftIsPressed;
	}

	bool Mouse::IsRightPressed() const noexcept
	{
		return rightIsPressed;
	}

	

	

	

	void Mouse::OnMouseMove(int x, int y) noexcept
	{
		Mouse::x = x;
		Mouse::y = y;

	}

	void Mouse::OnMouseLeave() noexcept
	{
		isInWindow = false;
	}

	void Mouse::OnMouseEnter() noexcept
	{
		isInWindow = true;
	}

	void Mouse::OnLeftPressed(int x, int y) noexcept
	{
		leftIsPressed = true;

	}

	void Mouse::OnLeftReleased(int x, int y) noexcept
	{
		leftIsPressed = false;

	}

	void Mouse::OnRightPressed(int x, int y) noexcept
	{
		rightIsPressed = true;

	}

	void Mouse::OnRightReleased(int x, int y) noexcept
	{
		rightIsPressed = false;

	}

	void Mouse::OnWheelUp(int x, int y) noexcept
	{
	}

	void Mouse::OnWheelDown(int x, int y) noexcept
	{
	}


	void Mouse::OnWheelDelta(int x, int y, int delta) noexcept
	{
		wheelDeltaCarry += delta;
		// generate events for every 120 
		while (wheelDeltaCarry >= WHEEL_DELTA)
		{
			wheelDeltaCarry -= WHEEL_DELTA;
			OnWheelUp(x, y);
		}
		while (wheelDeltaCarry <= -WHEEL_DELTA)
		{
			wheelDeltaCarry += WHEEL_DELTA;
			OnWheelDown(x, y);
		}
	}
}