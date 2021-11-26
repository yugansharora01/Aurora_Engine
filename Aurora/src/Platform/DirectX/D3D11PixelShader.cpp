#include "pch.h"
#include "D3D11PixelShader.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "d3dcompiler.h"

namespace Aurora {

	D3D11PixelShader::D3D11PixelShader(const std::wstring& path)
	{
		INFOMAN;

		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
		GFX_THROW_INFO(D3DReadFileToBlob(path.c_str(), &pBytecodeBlob));

		GFX_THROW_INFO(Getgfx()->GetDevice()->CreatePixelShader(
			pBytecodeBlob->GetBufferPointer(),
			pBytecodeBlob->GetBufferSize(),
			nullptr,
			&pPixelShader
		));
	}

	void D3D11PixelShader::Bind()
	{
		Getgfx()->GetContext()->PSSetShader(pPixelShader.Get(), nullptr, 0u);
		pConst->Bind();
	}
	
	void D3D11PixelShader::UploadFloat2(DirectX::XMFLOAT2 val)
	{
		pConst = std::make_shared<D3D11PixelConstantBuffer>();
		pConst->Create<DirectX::XMFLOAT2>(val);
	}
	
	void D3D11PixelShader::UploadFloat3(DirectX::XMFLOAT3 val)
	{
		pConst = std::make_shared<D3D11PixelConstantBuffer>();
		pConst->Create<DirectX::XMFLOAT3>(val);
	}
	
	void D3D11PixelShader::UploadFloat4(DirectX::XMFLOAT4 val)
	{
		pConst = std::make_shared<D3D11PixelConstantBuffer>();
		pConst->Create<DirectX::XMFLOAT4>(val);
	}

	void D3D11PixelShader::UploadMat3(DirectX::XMMATRIX mat3)
	{
		pConst = std::make_shared<D3D11PixelConstantBuffer>();
		pConst->Create<DirectX::XMMATRIX>(mat3);
	}
	
	void D3D11PixelShader::UploadMat4(DirectX::XMMATRIX mat4)
	{
		pConst = std::make_shared<D3D11PixelConstantBuffer>();
		pConst->Create<DirectX::XMMATRIX>(mat4);
	}
	void D3D11PixelShader::UploadMat4X8(std::array<DirectX::XMFLOAT4, 8> arr)
	{
		pConst = std::make_shared<D3D11PixelConstantBuffer>();
		pConst->Create<std::array<DirectX::XMFLOAT4, 8>>(arr);
	}
}