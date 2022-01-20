#include "pch.h"
#include "Model.h"
#include "Aurora/Scene/Components.h"

namespace Aurora {
	Model::Model(std::string path, std::wstring vShaderPath, std::wstring pShaderPath,bool compress)
		:ModelPath(path),IsCompressed(compress)
	{
		Assimp::Importer imp;
		auto model = imp.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

		if (IsCompressed)
		{
			Meshes.emplace_back(model, vShaderPath, pShaderPath);
		}
		else 
		{
			for (unsigned int i = 0; i < model->mNumMeshes; i++)
			{
				Meshes.emplace_back(model->mMeshes[i], vShaderPath, pShaderPath);
			}
		}
		
		
	}

	Mesh* Model::LoadModel(Ref<Entity> ParentEntity, Ref<Scene> scene)
	{
		
		if (Meshes.size() > 1)
		{
			for (size_t i = 0; i < Meshes.size(); i++)
			{
				auto e = scene->CreateChildEntity(ParentEntity, "Child");
				e->AddComponent<TransformComponent>(*ParentEntity->GetComponent<TransformComponent>());
				e->AddComponent<MeshComponent>(Meshes[i].vShader, Meshes[i].pShader,Meshes[i].vBuf,Meshes[i].iBuf);
			}
			Mesh m;
			m.IsEmpty = true;
			return &m;
		}
		else
		{
			return &Meshes[0];
		}
		
	}
	
	Mesh::Mesh(aiMesh* mesh,std::wstring vShaderPath, std::wstring pShaderPath)
	{
		vShader = VertexShader::Create(vShaderPath);
		pShader = PixelShader::Create(pShaderPath);

		std::vector<VertexData> vertices;
		vertices.reserve(mesh->mNumVertices);

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			VertexData data;
			data.pos = { mesh->mVertices[i].x,mesh->mVertices[i].y ,mesh->mVertices[i].z };
			data.normal = *reinterpret_cast<DirectX::XMFLOAT3*>(&mesh->mNormals[i]);
			vertices.push_back(data);
		}
		vBuf = VertexBuffer::Create(vertices);

		std::vector<LayoutBuffer> list;

		list.emplace_back("Position", 0u, PropertiesDataType::Float3, false, 32);
		list.emplace_back("Normal", 12, PropertiesDataType::Float3, false, 32);

		vBuf->SetLayout(list, vShader);

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

	}

	Mesh::Mesh(const aiScene* scene, std::wstring vShaderPath, std::wstring pShaderPath)
	{
		vShader = VertexShader::Create(vShaderPath);
		pShader = PixelShader::Create(pShaderPath);

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
				vertices.push_back(data);
			}
			
		}

		vBuf = VertexBuffer::Create(vertices);

		std::vector<LayoutBuffer> list;

		list.emplace_back("Position", 0u, PropertiesDataType::Float3, false, 32);
		list.emplace_back("Normal", 12, PropertiesDataType::Float3, false, 32);

		vBuf->SetLayout(list, vShader);

		vBuf->SetTopology(TopologyType::Triangle_List);
		
		iBuf = IndexBuffer::Create(indices);
	}

	

}