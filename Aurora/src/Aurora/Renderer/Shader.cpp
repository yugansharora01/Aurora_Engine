#include "pch.h"
#include "Shader.h"
#include "RendererAPI.h"
#include "Platform/DirectX/D3D11PixelShader.h"
#include "Platform/DirectX/D3D11VertexShader.h"
#include "Aurora/Utils/Convertors.h"

namespace Aurora {

	std::string PixelShader::path = "";
	std::string VertexShader::path = "";

	std::vector<Data> PixelShader::UploadData;
	std::vector<Data> VertexShader::UploadData;
	
	std::shared_ptr<PixelShader> PixelShader::Create(const std::wstring& Path)
	{
		
		path = ws2s(Path);
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); break;
		case RendererAPI::API::Direct3D: return std::make_shared<D3D11PixelShader>(Path); break;

		default:
			break;
		}

		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		
	}
	std::shared_ptr<VertexShader> VertexShader::Create(const std::wstring& Path)
	{
		path = ws2s(Path);
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); break;
		case RendererAPI::API::Direct3D: return std::make_shared<D3D11VertexShader>(Path); break;

		default:
			break;
		}

		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		
	}
}