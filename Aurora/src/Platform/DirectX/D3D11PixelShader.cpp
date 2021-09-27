#include "pch.h"
#include "D3D11PixelShader.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "d3dcompiler.h"

namespace Aurora {

	D3D11PixelShader::D3D11PixelShader(const std::wstring& path)
	{
		INFOMAN();

		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
		GFX_THROW_INFO(D3DReadFileToBlob(path.c_str(), &pBytecodeBlob));

		GFX_THROW_INFO(Getgfx().GetDevice()->CreatePixelShader(
			pBytecodeBlob->GetBufferPointer(),
			pBytecodeBlob->GetBufferSize(),
			nullptr,
			&pPixelShader
		));
	}

	void D3D11PixelShader::Bind() noexcept
	{
		Getgfx().GetContext()->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	}
}