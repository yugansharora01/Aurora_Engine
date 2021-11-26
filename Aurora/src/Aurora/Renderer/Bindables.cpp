#include "pch.h"
#include "Bindables.h"
#include "Aurora/Application.h"
#include "Aurora/Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Aurora {

	D3D11Graphics* Bindables::Getgfx()
	{
		auto gfx = Graphics::GraphicsObject;
		return &(*gfx);
	}
	
	DxgiInfoManager& Bindables::GetInfoManager() AU_DEBUGNOEXCEPT
	{
		// TODO: insert return statement here
		#ifdef AU_DEBUG
				return Getgfx()->GetInfoManager();
		#else
				throw std::logic_error("LOL XD Tried to Access InfoManager in Release Mode");
		#endif
	}
}