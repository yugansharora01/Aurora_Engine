#include "pch.h"
#include "D3D11PixelShader.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include <d3dcompiler.h>
#include "Aurora/Utils/Convertors.h"
#include "DirectXHelperFunc.h"

namespace Aurora {

	D3D11PixelShader::D3D11PixelShader(const std::string& Path)
	{
		path = Path;
		INFOMAN;

		
		GFX_THROW_INFO(CompileShader(s2ws(Path), "main", "ps_5_0", &pBytecodeBlob));

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
	}

	void D3D11PixelShader::Refresh()
	{
	}

}