#pragma once
#include "Aurora/Renderer/Buffer.h"
#include "Aurora/Renderer/Shader.h"
#include "Aurora/Scene/Scene.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


namespace Aurora {
	class MeshComponent;

	class Mesh
	{
	public:
		Mesh() = default;
		std::string Load(const aiScene* scene, aiMesh* mesh);
		std::string Load(const aiScene* scene);
		~Mesh() = default;
	public:
		Ref<VertexBuffer> vBuf;
		Ref<IndexBuffer> iBuf;
		bool IsEmpty = false;
	};


	class Model
	{
	public:
		Model(std::string path,bool compress = false);
		Mesh* LoadModel(Ref<Entity> ParentEntity,Ref<Scene> scene);
	public:
		std::vector<Mesh> Meshes;
		std::vector<std::string> paths;
		std::string ModelPath;
		std::string TexPath;
		bool IsCompressed = false;
	};

	
}


