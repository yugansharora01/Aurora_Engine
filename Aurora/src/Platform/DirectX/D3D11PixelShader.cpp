#include "pch.h"
#include "D3D11PixelShader.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include <d3dcompiler.h>
#include "Aurora/Utils/Convertors.h"
#include "DirectXHelperFunc.h"

namespace Aurora {

	D3D11PixelShader::D3D11PixelShader(const std::wstring& Path)
	{
		path = ws2s(Path);
		INFOMAN;

		
		GFX_THROW_INFO(CompileShader(Path, "main", "ps_5_0", &pBytecodeBlob));

		GFX_THROW_INFO(Getgfx()->GetDevice()->CreatePixelShader(
			pBytecodeBlob->GetBufferPointer(),
			pBytecodeBlob->GetBufferSize(),
			nullptr,
			&pPixelShader
		));
		pConst = CreateRef<D3D11PixelConstantBuffer>();
		pStructured = CreateRef<D3D11PixelStructuredBuffer>();
	}

	void D3D11PixelShader::Bind()
	{
		Getgfx()->GetContext()->PSSetShader(pPixelShader.Get(), nullptr, 0u);
		
		if (pConst->HaveData)
			pConst->Bind();
		
		if (pStructured->HaveData)
		{
			pStructured->Bind();
		}
		
	}

	void D3D11PixelShader::Refresh()
	{
		pConst = CreateRef<D3D11PixelConstantBuffer>();
		pStructured = CreateRef<D3D11PixelStructuredBuffer>();
	}

	void D3D11PixelShader::UploadData(void* val, size_t SizeOfEle, size_t SizeOfData, bool StoreData, int slot)
	{
		pConst->Create((unsigned int)SizeOfData, val,slot);
	}

	void D3D11PixelShader::UploadFloat(std::vector<float> vec, bool StoreData, int slot)
	{
		pConst->Create((unsigned int)(vec.size() * sizeof(float)), vec.data(), slot);
	}

	void D3D11PixelShader::UploadFloat2(std::vector<DirectX::XMFLOAT2> vec2, bool StoreData, int slot)
	{
		pConst->Create((unsigned int)(vec2.size() * sizeof(DirectX::XMFLOAT2)), vec2.data(), slot);
	}

	void D3D11PixelShader::UploadFloat3(std::vector<DirectX::XMFLOAT3> vec3, bool StoreData, int slot)
	{
		pConst->Create((unsigned int)(vec3.size() * sizeof(DirectX::XMFLOAT3)), vec3.data(), slot);
	}

	void D3D11PixelShader::UploadFloat4(std::vector<DirectX::XMFLOAT4> vec4, bool StoreData, int slot)
	{
		pConst->Create((unsigned int)(vec4.size() * sizeof(DirectX::XMFLOAT4)),vec4.data(), slot);

		if(StoreData)
			UploadedData.push_back(vec4);
	}

	void D3D11PixelShader::SetDataToAppend(unsigned int Elements, unsigned int EleSize,void* data)
	{
		pStructured->Create(Elements, EleSize, data);
	}

	void* D3D11PixelShader::GetAppendedData()
	{
		return pStructured->GetData();
	}
	
	
}