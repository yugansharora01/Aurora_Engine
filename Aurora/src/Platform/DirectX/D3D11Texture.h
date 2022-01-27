#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Aurora/Renderer/Texture.h"

namespace Aurora {

	class D3D11Texture : public Texture , public Bindables
	{
	public:
		D3D11Texture(const std::string path);
		void Bind();
		void Unbind() {}
	protected:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
	};
}