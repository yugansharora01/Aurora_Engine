#include "pch.h"
#include "Shader.h"
#include "RendererAPI.h"
#include "Platform/DirectX/D3D11PixelShader.h"
#include "Platform/DirectX/D3D11VertexShader.h"
#include "Aurora/Utils/Convertors.h"

namespace Aurora {

	Ref<Shader> Shader::Create(const std::string& path, ShaderType type)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::openGL:	AU_CORE_ASSERT(false, "RendererAPI::openGL is currently not supported!"); break;
		case RendererAPI::API::Direct3D: 
		{
			switch (type)
			{
			case Aurora::Shader::PixelShader: return CreateRef<D3D11PixelShader>(path);
				break;
			case Aurora::Shader::VertexShader: return CreateRef<D3D11VertexShader>(path);
				break;
			}
		}
		}

		AU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}