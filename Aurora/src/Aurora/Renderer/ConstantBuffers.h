#pragma once

#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class PixelConstantBuffer : public Bindables
	{
	public:
		virtual ~PixelConstantBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Update(const std::array<DirectX::XMFLOAT4, 8>& consts) = 0;
		
		static std::shared_ptr<PixelConstantBuffer> Create(std::array<DirectX::XMFLOAT4, 8> facecolors);

	};

	class VertexConstantBuffer : public Bindables
	{
	public:
		virtual ~VertexConstantBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Update(const DirectX::XMMATRIX& consts) = 0;


		static std::shared_ptr<VertexConstantBuffer> Create(DirectX::XMMATRIX mat);
	};

	
}