#include "pch.h"
#include "D3D11VertexShader.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "Aurora/Utils/Convertors.h"
#include "DirectXHelperFunc.h"

#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

namespace Aurora 
{

	D3D11VertexShader::D3D11VertexShader(const std::string& Path)
	{
		path = Path;
		INFOMAN;

		GFX_THROW_INFO(CompileShader(s2ws(Path), "main", "vs_5_0", &pBytecodeBlob));

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
		
		
	}

	void D3D11VertexShader::Refresh()
	{
	}

	ID3DBlob* D3D11VertexShader::GetBytecode() const noexcept
	{
		return pBytecodeBlob.Get();
	}

	
}