#include "pch.h"
#include "D3D11VertexShader.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "Aurora/Utils/Convertors.h"
#include "DirectXHelperFunc.h"

#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

namespace Aurora 
{

	D3D11VertexShader::D3D11VertexShader(const std::wstring& Path)
	{
		path = ws2s(Path);
		INFOMAN;

		GFX_THROW_INFO(CompileShader(Path, "main", "vs_5_0", &pBytecodeBlob));

		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateVertexShader(
			pBytecodeBlob->GetBufferPointer(),
			pBytecodeBlob->GetBufferSize(),
			nullptr,
			&pVertexShader
		));

		vConst = CreateRef<D3D11VertexConstantBuffer>();
	}

	void D3D11VertexShader::Bind() 
	{
		Getgfx()->GetContext()->VSSetShader(pVertexShader.Get(), nullptr, 0u);
		
		if(vConst->HaveData)
			vConst->Bind();
		
	}

	void D3D11VertexShader::Refresh()
	{
		vConst = CreateRef<D3D11VertexConstantBuffer>();
	}

	ID3DBlob* D3D11VertexShader::GetBytecode() const noexcept
	{
		return pBytecodeBlob.Get();
	}

	void D3D11VertexShader::UploadData(void* val, size_t SizeOfEle, size_t SizeOfData, bool StoreData, int slot)
	{
		vConst->Create((unsigned int)SizeOfData, val);
	}

	void D3D11VertexShader::UploadFloat(std::vector<float> vec, bool StoreData, int slot)
	{
		vConst->Create((unsigned int)(vec.size() * sizeof(float)), vec.data());

		//if (StoreData)
			//UploadedData.push_back(vec);
	}

	void D3D11VertexShader::UploadFloat2(std::vector<DirectX::XMFLOAT2> vec2, bool StoreData, int slot)
	{
		vConst->Create((unsigned int)(vec2.size() * sizeof(DirectX::XMFLOAT2)), vec2.data());
	}

	void D3D11VertexShader::UploadFloat3(std::vector<DirectX::XMFLOAT3> vec3, bool StoreData, int slot)
	{
		vConst->Create((unsigned int)(vec3.size() * sizeof(DirectX::XMFLOAT3)), vec3.data());
	}
	
	void D3D11VertexShader::UploadFloat4(std::vector<DirectX::XMFLOAT4> vec4, bool StoreData, int slot)
	{
		vConst->Create((unsigned int)(vec4.size() * sizeof(DirectX::XMFLOAT4)), vec4.data());
		
		if(StoreData)
			UploadedData.push_back(vec4);
	}
}