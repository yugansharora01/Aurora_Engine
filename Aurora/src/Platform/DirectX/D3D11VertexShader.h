#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Aurora/Renderer/Shader.h"
#include "D3D11Buffers.h"

namespace Aurora {

	class D3D11VertexShader : public VertexShader , public Bindables
	{
	public:
		D3D11VertexShader(const std::wstring& Path);

		void Bind() override;

		void Unbind() override {}

		virtual void Refresh() override;

		ID3DBlob* GetBytecode() const noexcept override;

		virtual void UploadData(void* val, size_t SizeOfEle, size_t SizeOfData, bool StoreData, int slot) override;

		virtual void UploadFloat(std::vector<float> vec, bool StoreData, int slot) override;

		virtual void UploadFloat2(std::vector<DirectX::XMFLOAT2> vec2, bool StoreData, int slot) override;

		virtual void UploadFloat3(std::vector<DirectX::XMFLOAT3> vec3, bool StoreData, int slot) override;

		virtual void UploadFloat4(std::vector<DirectX::XMFLOAT4> vec4, bool StoreData, int slot) override;

	private:
		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
		Ref<D3D11VertexConstantBuffer> vConst;
	};
}