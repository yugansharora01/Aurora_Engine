#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Aurora/Renderer/Shader.h"
#include "D3D11ConstantBuffers.h"
#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class D3D11PixelShader : public PixelShader , public Bindables
	{
		using Bindables::Getgfx;
		using Bindables::GetInfoManager;
	public:
		D3D11PixelShader(const std::wstring& path);
		void Bind() override;
		void Unbind() override {}

		virtual void UploadFloat2(DirectX::XMFLOAT2 val) override;
		virtual void UploadFloat3(DirectX::XMFLOAT3 val) override;
		virtual void UploadFloat4(DirectX::XMFLOAT4 val) override;
		virtual void UploadMat3(DirectX::XMMATRIX mat3) override;
		virtual void UploadMat4(glm::mat4 mat4) override;
		virtual void UploadMat4X8(std::array<DirectX::XMFLOAT4, 8> arr) override;
	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
		
		std::shared_ptr<D3D11ConstantBuffer> pConst;
	};

}