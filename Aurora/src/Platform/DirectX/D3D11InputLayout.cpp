#include "pch.h"
#include "D3D11InputLayout.h"
#include "Platform/Windows/GraphicsThrowMacros.h"

namespace Aurora {

	D3D11InputLayout::D3D11InputLayout(
		const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
		ID3DBlob* pVertexShaderBytecode)
	{
		INFOMAN();
		GFX_THROW_INFO(Getgfx().GetDevice()->CreateInputLayout(
			layout.data(), (UINT)layout.size(),
			pVertexShaderBytecode->GetBufferPointer(),
			pVertexShaderBytecode->GetBufferSize(),
			&pInputLayout
		));
	}

	void D3D11InputLayout::Bind() noexcept
	{
		Getgfx().GetContext()->IASetInputLayout(pInputLayout.Get());
	}
}