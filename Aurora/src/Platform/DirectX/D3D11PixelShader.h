#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Aurora/Renderer/Shader.h"
#include "D3D11Buffers.h"
#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class D3D11PixelShader : public Shader , public Bindables
	{
		using Bindables::Getgfx;
		using Bindables::GetInfoManager;
	public:
		D3D11PixelShader(const std::string& Path);
		virtual void Bind() override;
		virtual void Unbind() override {}
		virtual void Refresh() override;

		
	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
	};

}