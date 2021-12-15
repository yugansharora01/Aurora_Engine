#include "pch.h"
#include "D3D11VertexShader.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "Aurora/Utils/Convertors.h"

#include <d3dcompiler.h>

namespace Aurora {

	D3D11VertexShader::D3D11VertexShader(const std::wstring& Path)
	{
		path = ws2s(Path);
		INFOMAN;

		GFX_THROW_INFO(D3DReadFileToBlob(Path.c_str(), &pBytecodeBlob));
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateVertexShader(
			pBytecodeBlob->GetBufferPointer(),
			pBytecodeBlob->GetBufferSize(),
			nullptr,
			&pVertexShader
		));
	}

	void D3D11VertexShader::Bind() 
	{
		Getgfx()->GetContext()->VSSetShader(pVertexShader.Get(), nullptr, 0u);
		vConst->Bind();
	}

	ID3DBlob* D3D11VertexShader::GetBytecode() const noexcept 
	{
		return pBytecodeBlob.Get();
	}

	void D3D11VertexShader::UploadFloat2(DirectX::XMFLOAT2 val)
	{
	}
	void D3D11VertexShader::UploadFloat3(DirectX::XMFLOAT3 val)
	{
	}
	void D3D11VertexShader::UploadFloat4(DirectX::XMFLOAT4 val)
	{
	}
	void D3D11VertexShader::UploadMat3(DirectX::XMMATRIX mat3)
	{
	}
	void D3D11VertexShader::UploadMat4(DirectX::XMMATRIX mat4)
	{
		vConst = std::make_shared<D3D11VertexConstantBuffer>();
		vConst->Create<DirectX::XMMATRIX>(mat4);
		DirectX::XMFLOAT4X4 dest;
		DirectX::XMStoreFloat4x4(&dest, mat4);
		Data d;
		d.name = "Unnamed Data";
		for (int i = 0; i < 4; i++)
			d.data.emplace_back(dest.m[i]);

		UploadData.push_back(d);
	}

	void D3D11VertexShader::UploadMat4X8(std::array<DirectX::XMFLOAT4, 8> arr)
	{

	}
}