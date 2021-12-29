#include "pch.h"
#include "Aurora/Core/Input.h"
#include "Aurora/Application.h"
#include "Platform/Windows/WindowsWindow.h"


namespace Aurora
{
	bool Input::IsKeyPressed(KeyCode key)
	{
		return dynamic_cast<WindowsWindow*>(&Application::Get().GetWindow())->GetWin32WindowPtr()->kbd.IsKeyPressed(key);
	}


	bool IsAnotherKeyPressed(KeyCode key)
	{
		return dynamic_cast<WindowsWindow*>(&Application::Get().GetWindow())->GetWin32WindowPtr()->kbd.IsAnotherKeyPressed(key);
	}

	bool Input::IsMouseButtonPressed()
	{
		auto wnd = dynamic_cast<WindowsWindow*>(&Application::Get().GetWindow())->GetWin32WindowPtr();
		return wnd->mouse.IsRightPressed() || wnd->mouse.IsLeftPressed();
	}

	bool Input::IsRightMouseButtonPressed()
	{
		return dynamic_cast<WindowsWindow*>(&Application::Get().GetWindow())->GetWin32WindowPtr()->mouse.IsRightPressed();
	}

	bool Input::IsLeftMouseButtonPressed()
	{
		return dynamic_cast<WindowsWindow*>(&Application::Get().GetWindow())->GetWin32WindowPtr()->mouse.IsLeftPressed();
	}

	int Input::GetMouseX()
	{
		return dynamic_cast<WindowsWindow*>(&Application::Get().GetWindow())->GetWin32WindowPtr()->mouse.GetPosX();
	}

	int Input::GetMouseY()
	{
		return dynamic_cast<WindowsWindow*>(&Application::Get().GetWindow())->GetWin32WindowPtr()->mouse.GetPosY();
	}

	std::pair<int,int> Input::GetMouseCoord()
	{
		return dynamic_cast<WindowsWindow*>(&Application::Get().GetWindow())->GetWin32WindowPtr()->mouse.GetPos();
	}
}