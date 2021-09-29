#pragma once

#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class PixelConstantBuffer : public Bindables
	{
	public:
		virtual ~PixelConstantBuffer() = default;

		static std::shared_ptr<PixelConstantBuffer> Create();
		
		static std::shared_ptr<PixelConstantBuffer> Create(std::array<DirectX::XMFLOAT3, 8> facecolors);

	};

	class VertexConstantBuffer : public Bindables
	{
	public:
		virtual ~VertexConstantBuffer() = default;

		virtual ID3DBlob* GetBytecode() const noexcept = 0;

		static std::shared_ptr<VertexConstantBuffer> Create();

		static std::shared_ptr<VertexConstantBuffer> Create(DirectX::XMMATRIX mat);
	};


}