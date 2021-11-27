#include "pch.h"
#include "Graphics.h"
#include "Platform/DirectX/D3D11Graphics.h"
#include "Aurora/Renderer/RendererAPI.h"
#include "Aurora/Renderer/FrameBuffer.h"

namespace Aurora
{
	void* Graphics::NativeGraphicsObject = nullptr;
	Ref<FrameBuffer> Graphics::fbuf = nullptr;

#ifdef AU_PLATFORM_WINDOWS
	Ref<D3D11Graphics> Graphics::GraphicsObject = nullptr;
#endif // AU_PLATFORM_WINDOWS

	Graphics* Graphics::Create(void* arg)
	{
		

		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	
			AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); 
			break;

		case RendererAPI::API::Direct3D:
		{
			HWND hwnd = (HWND)arg;
			GraphicsObject = std::make_shared<D3D11Graphics>(hwnd);
			fbuf = FrameBuffer::Create(800, 600);
			return &(*GraphicsObject);
		}

		default:
			break;
		}

		
		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}