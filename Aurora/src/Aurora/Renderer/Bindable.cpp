#include "pch.h"
#include "Bindable.h"
#include <stdexcept>

namespace Aurora {

	ID3D11DeviceContext* Bindable::GetContext(Graphics& gfx) noexcept
	{
		return gfx.pContext.Get();
	}

	ID3D11Device* Bindable::GetDevice(Graphics& gfx) noexcept
	{
		return gfx.pDevice.Get();
	}

	DxgiInfoManager& Bindable::GetInfoManager(Graphics& gfx) noexcept(AU_DEBUG)
	{
	#ifndef AU_RELEASE
		return gfx.infoManager;
	#else
		throw std::logic_error("LOL XD Tried to Access InfoManager in Release Mode");
	#endif
	}
}