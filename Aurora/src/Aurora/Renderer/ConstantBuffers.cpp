#include "pch.h"
#include "ConstantBuffers.h"
#include "RendererAPI.h"
#include "Platform/DirectX/D3D11ConstantBuffers.h"

namespace Aurora {
	

	/*std::shared_ptr<PixelConstantBuffer> PixelConstantBuffer::Create(std::array<DirectX::XMFLOAT4, 8> facecolors)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); break;
		case RendererAPI::API::Direct3D: return std::make_shared<D3D11PixelConstantBuffer>(facecolors); break;

		default:
			break;
		}

		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		
	}

	std::shared_ptr<VertexConstantBuffer> VertexConstantBuffer::Create(DirectX::XMMATRIX mat)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); break;
		case RendererAPI::API::Direct3D: return std::make_shared<D3D11VertexConstantBuffer>(mat); break;

		default:
			break;
		}

		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		
	}*/

}