#pragma once

#include "Aurora/Renderer/Buffer.h"
#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class D3D11InputLayout : public InputLayout , public Bindables
	{
	public:
		D3D11InputLayout(
			const std::vector<LayoutBuffer>& layout,
			ID3DBlob* pVertexShaderBytecode
		);
		void Bind() override;
		void Unbind() override{}

	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	};
}