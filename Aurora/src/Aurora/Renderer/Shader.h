#pragma once

#include <DirectXMath.h>
#include <d3d11.h>


namespace Aurora {

	struct Data
	{
		unsigned int id;
		std::vector<DirectX::XMFLOAT4> data;
		Data() = default;
	};

	class Shader
	{
	public:
		enum ShaderType
		{
			PixelShader,
			VertexShader
		};

		std::string path;

		static Ref<Shader> Create(const std::string& path,ShaderType type);

		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		virtual void Refresh() = 0;
	};

}