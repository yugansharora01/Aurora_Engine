#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Aurora/Renderer/Shader.h"
#include "D3D11Buffers.h"
#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class D3D11PixelShader : public PixelShader , public Bindables
	{
		using Bindables::Getgfx;
		using Bindables::GetInfoManager;
	public:
		D3D11PixelShader(const std::wstring& Path);
		virtual void Bind() override;
		virtual void Unbind() override {}
		virtual void Refresh() override;

		virtual void UploadData(void* val, size_t SizeOfEle, size_t SizeOfData, bool StoreData, int slot) override;

		virtual void UploadFloat(std::vector<float> vec, bool StoreData, int slot) override;

		virtual void UploadFloat2(std::vector<DirectX::XMFLOAT2> vec2, bool StoreData, int slot) override;

		virtual void UploadFloat3(std::vector<DirectX::XMFLOAT3> vec3, bool StoreData, int slot) override;

		virtual void UploadFloat4(std::vector<DirectX::XMFLOAT4> vec4, bool StoreData, int slot) override;

		virtual void SetDataToAppend(unsigned int Elements, unsigned int EleSize, void* data) override;

		virtual void* GetAppendedData() override;

	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
		Ref<D3D11PixelConstantBuffer> pConst;
		Ref<D3D11PixelStructuredBuffer> pStructured;
	};

}