#include "pch.h"
#include "PixelShader.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "d3dcompiler.h"

PixelShader::PixelShader(Graphics& gfx, const std::wstring& path)
{
	INFOMAN(gfx);

	Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
	GFX_THROW_INFO(D3DReadFileToBlob(path.c_str(), &pBytecodeBlob));

	GFX_THROW_INFO(GetDevice(gfx)->CreatePixelShader(
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		nullptr,
		&pPixelShader
	));
}

void PixelShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
