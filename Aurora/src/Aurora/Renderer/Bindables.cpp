#include "pch.h"
#include "Bindables.h"
#include "Aurora/Application.h"
#include "Aurora/Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Aurora {

	Graphics& Bindables::Getgfx()
	{
		auto wnd = (Win32_Window*)Application::Get().GetWindow().GetNativeWindow();
		return wnd->Gfx();
	}
	DxgiInfoManager& Bindables::GetInfoManager() noexcept(AU_DEBUG)
	{
		// TODO: insert return statement here
		#ifndef AU_RELEASE
				return Getgfx().GetInfoManager();
		#else
				throw std::logic_error("LOL XD Tried to Access InfoManager in Release Mode");
		#endif
	}
}