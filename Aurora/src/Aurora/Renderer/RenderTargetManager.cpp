#include "pch.h"
#include "RenderTargetManager.h"
#include "Platform/DirectX/D3D11RenderTargetManager.h"

namespace Aurora {
	std::shared_ptr<RenderTargetManager> RenderTargetManager::Create(unsigned int width, unsigned int height)
	{
		return std::make_shared<D3D11RenderTargetManager>(width,height);
	}
}