#pragma once

//#include "Bindable.h"
#include "Aurora/Renderer/Buffer.h"
#include "Platform/Windows/GraphicsThrowMacros.h"

namespace Aurora {

	class D3D11VertexBuffer : public VertexBuffer
	{
	public:
		D3D11VertexBuffer(const std::vector<DirectX::XMFLOAT3>& vertices);
		
		void Bind() noexcept override;
		void Unbind() noexcept override{}

	private:
		UINT stride;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	};
}