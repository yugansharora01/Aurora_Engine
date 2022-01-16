#pragma once
#include "Aurora/Renderer/Buffer.h"
#include "Aurora/Renderer/Shader.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


namespace Aurora {
	class Mesh
	{
	public:
		Mesh(std::string path, std::wstring vShaderPath, std::wstring pShaderPath);
	public:
		Ref<VertexBuffer> vBuf;
		Ref<IndexBuffer> iBuf;
		Ref<VertexShader> vShader;
		Ref<PixelShader> pShader;
	};
}


