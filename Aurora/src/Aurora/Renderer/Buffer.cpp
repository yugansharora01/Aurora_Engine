#include "pch.h"
#include "Buffer.h"
#include "Platform/DirectX/D3D11IndexBuffer.h"
#include "Platform/DirectX/D3D11VertexBuffer.h"
#include "Platform/DirectX/D3D11InputLayout.h"


namespace Aurora {
	
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(const std::vector<DirectX::XMFLOAT3>& vertices)
	{
		return std::make_shared<D3D11VertexBuffer>(vertices);
	}
	
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(const std::vector<unsigned short>& indices)
	{
		return std::make_shared<D3D11IndexBuffer>(indices);
	}

	std::shared_ptr<InputLayout> InputLayout::Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVertexShaderBytecode)
	{
		return std::make_shared<D3D11InputLayout>(layout, pVertexShaderBytecode);
	}
}
