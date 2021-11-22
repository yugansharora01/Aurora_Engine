#include "pch.h"
#include "Graphics.h"
#include "Platform/DirectX/D3D11Graphics.h"
#include "Aurora/Renderer/RendererAPI.h"

namespace Aurora
{
	void* Graphics::NativeGraphicsObject = nullptr;

	Ref<Graphics> Graphics::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	
			AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); 
			break;

		case RendererAPI::API::Direct3D:
		{
			Ref<D3D11Graphics> graphic = CreateRef<D3D11Graphics>();
			NativeGraphicsObject = (void*)&(*graphic);
			return graphic; 
			break;
		}

		default:
			break;
		}

		
		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}