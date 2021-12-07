#include "pch.h"
#include "D3D11InputLayout.h"
#include "Platform/Windows/GraphicsThrowMacros.h"

namespace Aurora {


	DXGI_FORMAT GetFormat(LayoutBuffer lay)
	{
		if (lay.Is_Normalised)
		{
			if (lay.type == ShaderDataType::Uint)
			{
				switch (lay.NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8_UNORM; break;
				case 16: return DXGI_FORMAT_R16_UNORM; break;
				}
			}
			else {
				if (lay.type == ShaderDataType::Sint)
				{
					switch (lay.NumberOfBits)
					{
					case 8:  return DXGI_FORMAT_R8_SNORM; break;
					case 16: return DXGI_FORMAT_R16_SNORM; break;
					}
				}
			}
		}
		else {


			switch (lay.type)
			{
			case ShaderDataType::Float:
				switch (lay.NumberOfBits)
				{
				case 16: return DXGI_FORMAT_R16_FLOAT; 
				case 32: return DXGI_FORMAT_R32_FLOAT; 
				}
				break;
			case ShaderDataType::Float2:
				switch (lay.NumberOfBits)
				{
				case 16: return DXGI_FORMAT_R16G16_FLOAT; 
				case 32: return DXGI_FORMAT_R32G32_FLOAT; 
				}
				break;
			case ShaderDataType::Float3:
				return DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case ShaderDataType::Float4:
				switch (lay.NumberOfBits)
				{
				case 16: return DXGI_FORMAT_R16G16B16A16_FLOAT; 
				case 32: return DXGI_FORMAT_R32G32B32A32_FLOAT; 
				}
				break;
			case ShaderDataType::Uint:
				switch (lay.NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8_UINT; 
				case 16: return DXGI_FORMAT_R16_UINT; 
				case 32: return DXGI_FORMAT_R32_UINT; 
				}
				break;
			case ShaderDataType::Uint2:
				switch (lay.NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8G8_UINT; 
				case 16: return DXGI_FORMAT_R16G16_UINT; 
				case 32: return DXGI_FORMAT_R32G32_UINT; 
				}
				break;
			case ShaderDataType::Uint3:

				return DXGI_FORMAT_R32G32B32_UINT;
				break;
			case ShaderDataType::Uint4:
				switch (lay.NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8G8B8A8_UINT; 
				case 16: return DXGI_FORMAT_R16G16B16A16_UINT; 
				case 32: return DXGI_FORMAT_R32G32B32A32_UINT; 
				} 
				break;
			case ShaderDataType::Sint:
				switch (lay.NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8_SINT; 
				case 16: return DXGI_FORMAT_R16_SINT; 
				case 32: return DXGI_FORMAT_R32_SINT; 
				}
				break;
			case ShaderDataType::Sint2:
				switch (lay.NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8G8_SINT; 
				case 16: return DXGI_FORMAT_R16G16_SINT; 
				case 32: return DXGI_FORMAT_R32G32_SINT; 
				}
				break;
			case ShaderDataType::Sint3:
				return DXGI_FORMAT_R32G32B32_SINT;
				break;
			case ShaderDataType::Sint4:
				switch (lay.NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8G8B8A8_SINT; 
				case 16: return DXGI_FORMAT_R16G16B16A16_SINT; 
				case 32: return DXGI_FORMAT_R32G32B32A32_SINT;
				}
				break;
			case ShaderDataType::Unorm:
				switch (lay.NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8G8B8A8_UNORM;
				case 16: return DXGI_FORMAT_R16G16B16A16_UNORM;
				}
				break;
			default: 
				switch (lay.NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8G8B8A8_TYPELESS; 
				case 16: return DXGI_FORMAT_R16G16B16A16_TYPELESS;
				case 32: return DXGI_FORMAT_R32G32B32A32_TYPELESS;
				}
				break;
			}
		}
	}

	std::vector<D3D11_INPUT_ELEMENT_DESC> GetLayoutDesc(const std::vector<LayoutBuffer>& layout)
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> layoutdesc;
		int i = 0;
		//for (auto Layout : layout)
		for (auto i = 0; i < layout.size(); i++)
		{
			D3D11_INPUT_ELEMENT_DESC desc = { layout[i].name.c_str(),0,GetFormat(layout[i]),0,layout[i].offset,D3D11_INPUT_PER_VERTEX_DATA ,0 };
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