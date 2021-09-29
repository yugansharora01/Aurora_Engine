#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Aurora/Renderer/Shader.h"

namespace Aurora {

	class D3D11PixelShader : public PixelShader
	{
	public:
		D3D11PixelShader(const std::wstring& path);
		void Bind() override;
		void Unbind() override {}
	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	};
}