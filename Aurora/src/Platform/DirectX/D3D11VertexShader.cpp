#include "pch.h"
#include "D3D11VertexShader.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include <d3dcompiler.h>

namespace Aurora {

	D3D11VertexShader::D3D11VertexShader(const std::wstring& path)
	{
		INFOMAN;

		GFX_THROW_INFO(D3DReadFileToBlob(path.c_str(), &pBytecodeBlob));
		GFX_THROW_INFO(Getgfx().GetDevice()->CreateVertexShader(
			pBytecodeBlob->GetBufferPointer(),
			pBytecodeBlob->GetBufferSize(),
			nullptr,
			&pVertexShader
		));
	}

	void D3D11VertexShader::Bind() 
	{
		Getgfx().GetContext()->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	}

	ID3DBlob* D3D11VertexShader::GetBytecode() const noexcept
	{
		return pBytecodeBlob.Get();
	}
}