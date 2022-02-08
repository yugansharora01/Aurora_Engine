#include "pch.h"
#include "Model.h"
#include "Aurora/Scene/Components.h"
#include "Aurora/Utils/FileOperations.h"
#include "Aurora/Scene/Components.h"

namespace Aurora {
	Model::Model(std::string path,bool compress)
		:ModelPath(path),IsCompressed(compress)
	{
		Assimp::Importer imp;
		auto model = imp.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

		if (IsCompressed || model->mNumMeshes == 1)
		{
			Mesh m;
			TexPath = m.Load(model);
			Meshes.push_back(m);
		}
		else 
		{
			for (unsigned int i = 0; i < model->mNumMeshes; i++)
			{
				Mesh m;
				paths.push_back(m.Load(model,model->mMeshes[i]));
				Meshes.push_back(m);
			}
		}
		
		
	}

	Model::Model(std::vector<Mesh> m)
		:Meshes(m)
	{
	}

	Mesh* Model::LoadModel(Ref<Entity> ParentEntity, Ref<Scene> scene)
	{
		
		if (Meshes.size() > 1)
		{
			/*for (size_t i = 0; i < Meshes.size(); i++)
			{
				auto e = scene->CreateChildEntity(ParentEntity, "Child");
				e->AddComponent<TransformComponent>(*ParentEntity->GetComponent<TransformComponent>());
				e->AddComponent<MeshComponent>(Meshes[i].vShader, Meshes[i].pShader,Meshes[i].vBuf,Meshes[i].iBuf);
				e->GetComponent<MeshComponent>()->SetTexture(paths[i]);
			}*/
			Mesh m;
			m.IsEmpty = true;
			return &m;
		}
		else
		{
			return &Meshes[0];
		}
		
	}
	
	Mesh::Mesh(Ref<VertexBuffer> VertexBuf, Ref<IndexBuffer> IndexBuf)
		:vBuf(VertexBuf),iBuf(IndexBuf)
	{
	}

	std::string Mesh::Load(const aiScene* scene, aiMesh* mesh)
	{

		std::vector<VertexData> vertices;
		vertices.reserve(mesh->mNumVertices);

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			VertexData data;
			data.pos = { mesh->mVertices[i].x,mesh->mVertices[i].y ,mesh->mVertices[i].z };
			data.normal = *reinterpret_cast<DirectX::XMFLOAT3*>(&mesh->mNormals[i]);
			data.texCoord = *reinterpret_cast<DirectX::XMFLOAT2*>(&mesh->mTextureCoords[0][i]);
			vertices.push_back(data);
		}
		vBuf = VertexBuffer::Create(vertices);

		

		vBuf->SetTopology(TopologyType::Triangle_List);

		std::vector<unsigned short> indices;
		indices.reserve(mesh->mNumFaces * 3);
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			const auto& face = mesh->mFaces[i];
			assert(face.mNumIndices == 3);
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}
		iBuf = IndexBuffer::Create(indices);

		if (mesh->mMaterialIndex >= 0)
		{
			auto& material = *scene->mMaterials[mesh->mMaterialIndex];
			aiString texfilename;
			material.GetTexture(aiTextureType_DIFFUSE, 0, &texfilename);
			std::string str(texfilename.C_Str());
			return str;
		}

	}

	std::string Mesh::Load(const aiScene* scene)
	{
		std::string texPath;
		

		std::vector<VertexData> vertices;

		std::vector<unsigned short> indices;

		for (unsigned int j = 0; j < scene->mNumMeshes; j++)
		{
			auto mesh = scene->mMeshes[j];

			indices.reserve((mesh->mNumFaces * 3) + indices.size());
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				const auto& face = mesh->mFaces[i];
				assert(face.mNumIndices == 3);
				auto LastVertexIndex = (unsigned int)vertices.size();
				indices.push_back(face.mIndices[0] + LastVertexIndex);
				indices.push_back(face.mIndices[1] + LastVertexIndex);
				indices.push_back(face.mIndices[2] + LastVertexIndex);
			}

			vertices.reserve(mesh->mNumVertices + vertices.size());
			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				VertexData data;
				data.pos = { mesh->mVertices[i].x,mesh->mVertices[i].y ,mesh->mVertices[i].z };
				data.normal = *reinterpret_cast<DirectX::XMFLOAT3*>(&mesh->mNormals[i]);
				data.texCoord = *reinterpret_cast<DirectX::XMFLOAT2*>(&mesh->mTextureCoords[0][i]);
				vertices.push_back(data);
			}
			

			if (mesh->mMaterialIndex >= 0)
			{
				auto& material = *scene->mMaterials[mesh->mMaterialIndex];
				aiString texfilename;
				material.GetTexture(aiTextureType_DIFFUSE, 0, &texfilename);
				texPath = std::string(texfilename.C_Str());
			}
		}

		vBuf = VertexBuffer::Create(vertices);

		

		vBuf->SetTopology(TopologyType::Triangle_List);
		
		iBuf = IndexBuffer::Create(indices);

		return texPath;
	}

	

}