#pragma once

#include "Aurora/Renderer/Buffer.h"

namespace Aurora {

	class D3D11InputLayout : public InputLayout
	{
	public:
		D3D11InputLayout(
			const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
			ID3DBlob* pVertexShaderBytecode
		);
		void Bind() noexcept override;

	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	};
}