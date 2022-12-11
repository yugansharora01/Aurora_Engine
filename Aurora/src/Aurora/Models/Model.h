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
		Mesh(Ref<VertexBuffer> VertexBuf, Ref<IndexBuffer> IndexBuf);
		std::string Load(const aiScene* scene, aiMesh* mesh);
		std::string Load(const aiScene* scene);
		~Mesh() = default;
	public:
		Ref<VertexBuffer> vBuf;
		Ref<IndexBuffer> iBuf;
		std::string name;
		bool IsEmpty = false;
	};


	class Model
	{
	public:
		Model(std::string path,bool compress = false);
		Model(std::vector<Mesh> m);
		Mesh* LoadModel(Ref<Entity> ParentEntity,Ref<Scene> scene);
	public:
		std::vector<Mesh> Meshes;
		std::vector<std::string> paths;
		std::string ModelPath;
		std::string TexPath;
		bool IsCompressed = false;
	};

	
}


