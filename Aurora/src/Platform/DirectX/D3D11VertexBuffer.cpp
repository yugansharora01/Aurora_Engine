#include "pch.h"
#include "D3D11VertexBuffer.h"
#include "D3D11VertexShader.h"
#include "D3D11Topology.h"
#include "D3D11InputLayout.h"

namespace Aurora {
	
	D3D11VertexBuffer::D3D11VertexBuffer(const std::vector<VertexData>& vertices)
	{
		INFOMAN;

		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = UINT(sizeof(VertexData) * vertices.size());
		bd.StructureByteStride = sizeof(VertexData);

		stride = sizeof(VertexData);

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();

		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateBuffer(&bd, &sd, &pVertexBuffer));
		
	}

	void D3D11VertexBuffer::Bind() 
	{
		const UINT offset = 0u;
		Getgfx()->GetContext()->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
		m_layout->Bind();
		m_topology->Bind();
	}
	void D3D11VertexBuffer::SetData(void* data, unsigned int size)
	{
		INFOMAN;

		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = UINT(size);
		bd.StructureByteStride = sizeof(DirectX::XMFLOAT3);

		stride = sizeof(DirectX::XMFLOAT3);

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = data;

		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateBuffer(&bd, &sd, &pVertexBuffer));
	}

	void D3D11VertexBuffer::SetLayout(std::vector<LayoutBuffer> layout, std::shared_ptr<VertexShader> vShader)
	{
		//ID3DBlob* blob = std::dynamic_pointer_cast<D3D11VertexShader>(vShader)->GetBytecode();
		m_layout = std::make_shared<D3D11InputLayout>(layout,vShader->GetBytecode());
	}

	void D3D11VertexBuffer::SetTopology(TopologyType type)
	{
		m_topology = std::make_shared<D3D11Topology>(type);
	}


}