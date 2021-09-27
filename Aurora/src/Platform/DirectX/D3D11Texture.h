#pragma once

#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class D3D11Texture : public Bindables
	{
	public:
		D3D11Texture(const class Surface& s);
		void Bind() noexcept override;
	protected:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
	};
}