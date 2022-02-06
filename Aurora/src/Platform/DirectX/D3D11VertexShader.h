#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Aurora/Renderer/Shader.h"
#include "D3D11Buffers.h"

namespace Aurora {

	class D3D11VertexShader : public Shader , public Bindables
	{
	public:
		D3D11VertexShader(const std::string& Path);

		void Bind() override;

		void Unbind() override {}

		virtual void Refresh() override;

		ID3DBlob* GetBytecode() const noexcept;

	private:
		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	};
}