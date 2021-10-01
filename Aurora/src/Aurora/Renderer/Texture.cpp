#include "pch.h"
#include "Texture.h"
#include "RendererAPI.h"
#include "Platform/DirectX/D3D11Texture.h"

namespace Aurora {
	
	std::shared_ptr<Texture> Texture::Create(const Surface& s)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); break;
		case RendererAPI::API::Direct3D: return std::make_shared<D3D11Texture>(s); break;

		default:
			break;
		}

		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		
	}

}