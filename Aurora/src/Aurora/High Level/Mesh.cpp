#include "pch.h"
#include "Mesh.h"

namespace Aurora {
	Mesh::Mesh(std::string path, std::wstring vShaderPath, std::wstring pShaderPath)
	{

		vShader = VertexShader::Create(vShaderPath);
		pShader = PixelShader::Create(pShaderPath);

		Assimp::Importer imp;
		auto model = imp.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

		const auto mesh = model->mMeshes[0];

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
}