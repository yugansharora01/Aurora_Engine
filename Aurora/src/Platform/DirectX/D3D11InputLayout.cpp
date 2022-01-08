#include "pch.h"
#include "D3D11InputLayout.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "DirectXHelperFunc.h"

namespace Aurora {

	std::vector<D3D11_INPUT_ELEMENT_DESC> GetLayoutDesc(const std::vector<LayoutBuffer>& layout)
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> layoutdesc;
		int i = 0;
		//for (auto Layout : layout)
		for (auto i = 0; i < layout.size(); i++)
		{
			auto format = GetPropertiesFormat(layout[i].Is_Normalised, layout[i].type, layout[i].NumberOfBits);
			D3D11_INPUT_ELEMENT_DESC desc = { layout[i].name.c_str(),0,format,0,layout[i].offset,D3D11_INPUT_PER_VERTEX_DATA ,0 };
			layoutdesc.push_back(desc);
		
		}
		return layoutdesc;
	}

	D3D11InputLayout::D3D11InputLayout(
		const std::vector<LayoutBuffer>& layout,
		ID3DBlob* pVertexShaderBytecode)
	{

		auto layoutdesc = GetLayoutDesc(layout);
		
		
		INFOMAN;
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateInputLayout(
			layoutdesc.data(), (UINT)layout.size(),
			pVertexShaderBytecode->GetBufferPointer(),
			pVertexShaderBytecode->GetBufferSize(),
			&pInputLayout
		));
	}

	void D3D11InputLayout::Bind() 
	{
		Getgfx()->GetContext()->IASetInputLayout(pInputLayout.Get());
	}
}