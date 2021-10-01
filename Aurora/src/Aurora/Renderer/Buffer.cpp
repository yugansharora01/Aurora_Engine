#include "pch.h"
#include "Buffer.h"
#include "RendererAPI.h"
#include "Platform/DirectX/D3D11IndexBuffer.h"
#include "Platform/DirectX/D3D11VertexBuffer.h"
#include "Platform/DirectX/D3D11InputLayout.h"
#include "Platform/DirectX/D3D11Topology.h"


namespace Aurora {
	
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(const std::vector<DirectX::XMFLOAT3>& vertices)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); break;
		case RendererAPI::API::Direct3D: return std::make_shared<D3D11VertexBuffer>(vertices); break;
		
		default:
			break;
		}

		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(const std::vector<unsigned short>& indices)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); break;
		case RendererAPI::API::Direct3D: return std::make_shared<D3D11IndexBuffer>(indices); break;

		default:
			break;
		}

		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		
	}

	std::shared_ptr<InputLayout> InputLayout::Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVertexShaderBytecode)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); break;
		case RendererAPI::API::Direct3D: return std::make_shared<D3D11InputLayout>(layout, pVertexShaderBytecode); break;

		default:
			break;
		}

		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		
	}
	
	std::shared_ptr<Topology> Topology::Create(TopologyType Type)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); break;
		case RendererAPI::API::Direct3D: return std::make_shared<D3D11Topology>(Type); break;

		default:
			break;
		}

		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		
	}
}
