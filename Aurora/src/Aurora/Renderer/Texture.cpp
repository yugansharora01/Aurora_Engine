#include "pch.h"
#include "Texture.h"
#include "Platform/DirectX/D3D11Texture.h"

namespace Aurora {
	
	std::shared_ptr<Texture> Texture::Create(const Surface& s)
	{
		return std::make_shared<D3D11Texture>(s);
	}

}