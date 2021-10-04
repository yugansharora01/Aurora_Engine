#pragma once

#include "Aurora/Renderer/Buffer.h"

namespace Aurora {

	class D3D11InputLayout : public InputLayout
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