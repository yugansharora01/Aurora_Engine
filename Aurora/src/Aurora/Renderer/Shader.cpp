#include "pch.h"
#include "Shader.h"
#include "Platform/DirectX/D3D11PixelShader.h"
#include "Platform/DirectX/D3D11VertexShader.h"

namespace Aurora {
	
	std::shared_ptr<PixelShader> PixelShader::Create(const std::wstring& path)
	{
		return std::make_shared<D3D11PixelShader>(path);
	}
	std::shared_ptr<VertexShader> VertexShader::Create(const std::wstring& path)
	{
		return std::make_shared<D3D11VertexShader>(path);
	}
}