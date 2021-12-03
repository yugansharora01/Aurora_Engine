#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Aurora/Renderer/Shader.h"
#include "D3D11ConstantBuffers.h"

namespace Aurora {

	class D3D11VertexShader : public VertexShader , public Bindables
	{
	public:
		D3D11VertexShader(const std::wstring& path);
		void Bind();
		void Unbind() {}
		ID3DBlob* GetBytecode() const noexcept override;

		virtual void UploadFloat2(DirectX::XMFLOAT2 val) override;
		virtual void UploadFloat3(DirectX::XMFLOAT3 val) override;
		virtual void UploadFloat4(DirectX::XMFLOAT4 val) override;
		virtual void UploadMat3(DirectX::XMMATRIX mat3) override;
		virtual void UploadMat4(glm::mat4 mat4) override;
		virtual void UploadMat4X8(std::array<DirectX::XMFLOAT4, 8> arr) override;

	private:
		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
		std::shared_ptr<D3D11ConstantBuffer> vConst;
	};
}