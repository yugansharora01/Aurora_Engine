#pragma once

#include "Platform/DirectX/D3D11Graphics.h"
#include "Platform/Windows/DxgiInfoManager.h"

namespace Aurora {
	class Bindables
	{
	public:
		static Ref<D3D11Graphics> Getgfx();
		static DxgiInfoManager& GetInfoManager() AU_DEBUGNOEXCEPT;
	};
}