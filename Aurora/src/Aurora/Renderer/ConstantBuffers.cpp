#include "pch.h"
#include "ConstantBuffers.h"
#include "Platform/DirectX/D3D11ConstantBuffers.h"

namespace Aurora {
	

	std::shared_ptr<PixelConstantBuffer> PixelConstantBuffer::Create(std::array<DirectX::XMFLOAT4, 8> facecolors)
	{
		return std::make_shared<D3D11PixelConstantBuffer>(facecolors);
	}

	std::shared_ptr<VertexConstantBuffer> VertexConstantBuffer::Create(DirectX::XMMATRIX mat)
	{
		return std::make_shared<D3D11VertexConstantBuffer>(mat);
	}

}