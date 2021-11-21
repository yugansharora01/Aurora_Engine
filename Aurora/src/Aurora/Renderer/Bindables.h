#pragma once

#include "Platform/DirectX/D3D11Graphics.h"
#include "Platform/Windows/DxgiInfoManager.h"

namespace Aurora {
	class Bindables
	{
	public:
		D3D11Graphics& Bindables::Getgfx()
		{
			auto wnd = Application::Get().GetWindow();
			//Graphics gfx = *wnd.Gfx();
			D3D11Graphics* g = dynamic_cast<D3D11Graphics*>((&wnd.Gfx()));
			return *wnd.Gfx();
		}
		static DxgiInfoManager& GetInfoManager() AU_DEBUGNOEXCEPT;
	};
}