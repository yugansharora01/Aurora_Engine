#include "pch.h"
#include "Graphics.h"
#include "Platform/DirectX/D3D11Graphics.h"
#include "Aurora/Renderer/RendererAPI.h"
#include "Aurora/Renderer/FrameBuffer.h"

namespace Aurora
{
	Ref<FrameBuffer> Graphics::fbuf = nullptr;


	Ref<Graphics> Graphics::Create(void* arg)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	
			AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); 
			break;

		case RendererAPI::API::Direct3D:
		{
			HWND hwnd = (HWND)arg;
			auto GraphicsObject = CreateRef<D3D11Graphics>(hwnd);
			return GraphicsObject;
		}

		default:
			break;
		}

		
		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Graphics> Graphics::Create(void* arg, unsigned int width, unsigned int height)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:
			AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!");
			break;

		case RendererAPI::API::Direct3D:
		{
			HWND hwnd = (HWND)arg;
			auto GraphicsObject = CreateRef<D3D11Graphics>(hwnd,width,height);
			return GraphicsObject;
		}

		default:
			break;
		}


		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}