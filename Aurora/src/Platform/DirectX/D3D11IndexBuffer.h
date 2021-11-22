#pragma once

#include "Aurora/Renderer/Buffer.h"
#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class D3D11IndexBuffer : public IndexBuffer , public Bindables
	{
	public:
		D3D11IndexBuffer(const std::vector<unsigned short>& indices);
		void Bind() override;
		void Unbind() override;
		UINT GetCount() const noexcept;

	private:
		UINT count;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	};
}
