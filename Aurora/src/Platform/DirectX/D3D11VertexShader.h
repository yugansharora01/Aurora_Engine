#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Aurora/Renderer/Shader.h"

namespace Aurora {

	class D3D11VertexShader : public VertexShader
	{
	public:
		D3D11VertexShader(const std::wstring& path);
		void Bind() noexcept override;
		ID3DBlob* GetBytecode() const noexcept override;

	private:
		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	};
}