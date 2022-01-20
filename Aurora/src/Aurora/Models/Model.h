#pragma once
#include "Aurora/Renderer/Buffer.h"
#include "Aurora/Renderer/Shader.h"
#include "Aurora/Scene/Scene.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


namespace Aurora {

	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(aiMesh* mesh, std::wstring vShaderPath, std::wstring pShaderPath);
		Mesh(const aiScene* scene, std::wstring vShaderPath, std::wstring pShaderPath);
		~Mesh() = default;
	public:
		Ref<VertexBuffer> vBuf;
		Ref<IndexBuffer> iBuf;
		Ref<VertexShader> vShader;
		Ref<PixelShader> pShader;
		bool IsEmpty = false;
	};


	class Model
	{
	public:
		Model(std::string path, std::wstring vShaderPath, std::wstring pShaderPath,bool compress = false);
		Mesh* LoadModel(Ref<Entity> ParentEntity,Ref<Scene> scene);
	public:
		std::vector<Mesh> Meshes;
		std::string ModelPath;
		bool IsCompressed = false;
	};

	
}


