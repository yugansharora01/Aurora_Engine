#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Aurora/Renderer/Texture.h"

namespace Aurora {

	class D3D11Texture : public Texture , public Bindables
	{
	public:
		D3D11Texture(const std::string path);
		D3D11Texture(const unsigned char* image,unsigned int pitch);
		void Bind();
		void Unbind() {}
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetShaderResource() { return pTextureView; }
	protected:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
	};
}