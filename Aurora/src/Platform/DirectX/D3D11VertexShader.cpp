#include "pch.h"
#include "D3D11VertexShader.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "Aurora/Utils/Convertors.h"

#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

namespace Aurora {

	HRESULT CompileShaderps(std::wstring srcFile, std::string entryPoint, std::string profile, ID3DBlob** blob)
	{
		//if (srcFile.empty() || entryPoint.empty() || profile.empty() || blob)
			//return E_INVALIDARG;

		*blob = nullptr;

		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( AU_DEBUG )
		flags |= D3DCOMPILE_DEBUG;
#endif

		const D3D_SHADER_MACRO defines[] =
		{
			"EXAMPLE_DEFINE", "1",
			NULL, NULL
		};

		ID3DBlob* shaderBlob = nullptr;
		ID3DBlob* errorBlob = nullptr;
		HRESULT hr = D3DCompileFromFile(srcFile.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entryPoint.c_str(), profile.c_str(),
			flags, 0, &shaderBlob, &errorBlob);
		if (FAILED(hr))
		{
			if (errorBlob)
			{
				OutputDebugStringA((char*)errorBlob->GetBufferPointer());
				errorBlob->Release();
			}

			if (shaderBlob)
				shaderBlob->Release();

			return hr;
		}

		*blob = shaderBlob;

		return hr;
	}

	D3D11VertexShader::D3D11VertexShader(const std::wstring& Path)
	{
		path = ws2s(Path);
		INFOMAN;

		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob1;
		GFX_THROW_INFO(CompileShaderps(Path, "main", "vs_4_0_level_9_1", &pBytecodeBlob));

		//GFX_THROW_INFO(D3DReadFileToBlob(Path.c_str(), &pBytecodeBlob));
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
		//Data d;
		//d.name = "Unnamed Data";
		std::vector<DirectX::XMFLOAT4> vec;
		for (int i = 0; i < 4; i++)
		{
			vec.emplace_back(dest.m[i]);
		}

		/*for (int i = 0; i < 4; i++)
			d.data.emplace_back(dest.m[i]);*/

		UploadData.push_back(vec);
	}

	void D3D11VertexShader::UploadMat4X8(std::array<DirectX::XMFLOAT4, 8> arr)
	{

	}
}