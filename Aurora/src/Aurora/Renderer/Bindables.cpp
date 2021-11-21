#include "pch.h"
#include "Bindables.h"
#include "Aurora/Application.h"
#include "Aurora/Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Aurora {


	
	DxgiInfoManager& Bindables::GetInfoManager() AU_DEBUGNOEXCEPT
	{
		// TODO: insert return statement here
		#ifdef AU_DEBUG
				return Getgfx().GetInfoManager();
		#else
				throw std::logic_error("LOL XD Tried to Access InfoManager in Release Mode");
		#endif
	}
}