#include "pch.h"
#include "ConstantBuffers.h"
#include "Platform/DirectX/D3D11ConstantBuffers.h"

namespace Aurora {
	
	std::shared_ptr<PixelConstantBuffer> PixelConstantBuffer::Create()
	{
		return std::make_shared<D3D11PixelConstantBuffer<std::array<DirectX::XMFLOAT3, 8>>>();
	}

	std::shared_ptr<PixelConstantBuffer> PixelConstantBuffer::Create(std::array<DirectX::XMFLOAT3, 8> facecolors)
	{
		return std::make_shared<D3D11PixelConstantBuffer<std::array<DirectX::XMFLOAT3, 8>>>(facecolors);
	}

	std::shared_ptr<VertexConstantBuffer> VertexConstantBuffer::Create()
	{
		return std::make_shared<D3D11VertexConstantBuffer<DirectX::XMMATRIX>>();
	}

	std::shared_ptr<VertexConstantBuffer> VertexConstantBuffer::Create(DirectX::XMMATRIX mat)
	{
		return std::make_shared<D3D11VertexConstantBuffer<DirectX::XMMATRIX>>(mat);
	}

}