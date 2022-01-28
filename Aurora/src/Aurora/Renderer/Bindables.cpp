#include "pch.h"
#include "Bindables.h"
#include "Aurora/Core/Application.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Aurora {

	Ref<D3D11Graphics> Bindables::Getgfx()
	{
		//auto gfx = Graphics::GraphicsObject;
		auto gfx = std::dynamic_pointer_cast<D3D11Graphics>(Application::Get().GetWindow().Gfx());
		
		return gfx;
	}
	
	DxgiInfoManager& Bindables::GetInfoManager() AU_DEBUGNOEXCEPT
	{
		// TODO: insert return statement here
		#ifdef AU_DEBUG
				return Getgfx()->GetInfoManager();
		#else
				throw std::logic_error("Tried to Access InfoManager in Release Mode");
		#endif
	}
}