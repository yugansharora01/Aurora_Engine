#include "pch.h"
#include "Renderer.h"
#include "Aurora/Core/Application.h"
#include "Aurora/Core/Window.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Aurora/Utils/FileOperations.h"
#include "Aurora/Models/Light.h"
#include "Aurora/Renderer/EditorCamera.h"

namespace Aurora 
{

	std::vector<std::string> Renderer::ModelPaths;
	RenderQueue Renderer::s_queue;
	bool Renderer::hasLights = false;
	std::vector<DirectX::XMFLOAT4> Renderer::data;
	Ref<D3D11PixelConstantBuffer> Renderer::pConst;
	Ref<D3D11VertexConstantBuffer> Renderer::vConst;
	DirectX::XMMATRIX Renderer::ViewMat;
	DirectX::XMMATRIX Renderer::ProjMat;

	std::vector<DirectX::XMFLOAT4> GetVec(std::vector<DirectX::XMMATRIX> matVec)
	{
		std::vector<DirectX::XMFLOAT4> vec;
		DirectX::XMFLOAT4X4 dest;
		for (size_t i = 0; i < matVec.size(); i++)
		{
			DirectX::XMStoreFloat4x4(&dest, matVec[i]);
			vec.emplace_back(dest._11, dest._12, dest._13, dest._14);
			vec.emplace_back(dest._21, dest._22, dest._23, dest._24);
			vec.emplace_back(dest._31, dest._32, dest._33, dest._34);
			vec.emplace_back(dest._41, dest._42, dest._43, dest._44);
		}

		return vec;
	}

	DirectX::XMMATRIX GetMatrix(ModelProperties ModelProp)
	{
		auto translate = ModelProp.translate;
		auto rotation = ModelProp.rotation;
		auto scale = ModelProp.scale;

		DirectX::XMFLOAT4 zero(0.0f, 0.0f, 0.0f, 0.0f);
		DirectX::XMFLOAT4 identity(1.0f, 0.0f, 0.0f, 0.0f);;
		auto zeroVec = DirectX::XMLoadFloat4(&zero);
		auto translateVec = DirectX::XMLoadFloat3(&translate);
		auto rotationVec = DirectX::XMLoadFloat3(&rotation);
		auto scaleVec = DirectX::XMLoadFloat3(&scale);
		auto identityQuat = DirectX::XMLoadFloat4(&identity);

		return DirectX::XMMatrixTransformation(zeroVec, identityQuat, scaleVec, zeroVec, DirectX::XMQuaternionRotationRollPitchYawFromVector(rotationVec), translateVec);
	}

	void ModelTexture::AddTexture(std::string tex, TextureType type)
	{
		Textures.insert({ type,tex });
	}

	bool ModelTexture::HaveTex(TextureType type)
	{
		return Textures.contains(type);
	}

	std::string ModelTexture::GetTex(TextureType type)
	{
		return Textures[type];
	}

	void Renderer::Init()
	{
		
	}

	void Renderer::ShutDown()
	{
		//TO DO Free everything if anything is required to be freed
	}

	void Renderer::BeginScene(Ref<Camera> camera,std::vector<Light> lights)
	{
		//TO DO it will take camera and other scene parameters

		ViewMat = DirectX::XMMatrixInverse(NULL, camera->GetTransform());

		ProjMat = camera->GetProjection();

		if (!lights.empty())
			hasLights = true;

		for (size_t i = 0; i < lights.size(); i++)
		{
			DirectX::XMFLOAT4 temp;
			auto LOL = DirectX::XMLoadFloat3(&lights[i].Position);
			DirectX::XMStoreFloat4(&temp, DirectX::XMVector4Transform(LOL, ViewMat));

			data.push_back(temp);
			data.push_back(lights[i].ambient);
			data.push_back(lights[i].diffuseColor);

			DirectX::XMFLOAT4 LightConstants;
			LightConstants.x = lights[i].diffuseIntensity;
			LightConstants.y = lights[i].attConst;
			LightConstants.z = lights[i].attLin;
			LightConstants.w = lights[i].attQuad;
			data.push_back(LightConstants);
		}

		
	}

	void Renderer::EndScene()
	{
		auto gfx = Application::Get().GetWindow().Gfx();

		for (auto& e : s_queue.Models)
		{
			auto& l = e.second;

			Bind(l);
			
			gfx->DrawIndexed(l.ibuf->GetCount());
		}

		s_queue.Models.clear();
	}


	void Renderer::DrawModel(std::string ModelName, ModelProperties ModelProp)
	{
		std::string ModelPath = FilesManager::GetPath(ModelName,PathType::ModelPath);
		s_queue.submit(ModelPath, ModelProp);
		ModelPaths.push_back(ModelPath);
	}

	void Renderer::Bind(ModelData modelData)
	{
		pConst->Bind();
		vConst->Bind();
		modelData.vbuf->Bind();
		modelData.vshader->Bind();
		modelData.pshader->Bind();
		modelData.ibuf->Bind();
		if (modelData.Textures.HaveTex(ModelTexture::Albedo))
		{
			Ref<Texture> t = Texture::Create(modelData.Textures.GetTex(ModelTexture::Albedo));
			t->Bind();
		}
	}

	void Renderer::SetData(ModelData modelData)
	{
		auto& path = modelData.pshader->path;
		std::vector<DirectX::XMMATRIX> matVec;

		if(path == "../Aurora/src/Aurora/Shaders/ColorIndexPS.hlsl")
		{
			//pShader->UploadFloat4(pShader->UploadedData[0], false, 0);
			matVec.push_back(DirectX::XMMatrixTranspose(
				modelData.mat * ViewMat * ProjMat));
		}
		else
		{
			if (path == "../Aurora/src/Aurora/Shaders/SolidPS.hlsl")
			{
				std::vector<DirectX::XMFLOAT4> color;
				color.push_back(modelData.MiscelData[0]);
				pConst->Create(color.size() * sizeof(DirectX::XMFLOAT4), color.data());
				//pShader->UploadFloat4(color, false, 0);
				matVec.push_back(DirectX::XMMatrixTranspose(
					modelData.mat * ViewMat * ProjMat));
			}
			else {
				//pShader->UploadFloat4(Light, false, 0);
				pConst->Create(data.size() * sizeof(DirectX::XMFLOAT4), data.data(), 0u);
				matVec.push_back(DirectX::XMMatrixTranspose(modelData.mat * ViewMat));
				matVec.push_back(DirectX::XMMatrixTranspose(
					modelData.mat * ViewMat * ProjMat));


				std::vector<DirectX::XMFLOAT4> material;
				material.push_back(modelData.MiscelData[0]);
				DirectX::XMFLOAT4 temp;
				temp.x = modelData.MiscelData[1].x;
				temp.y = modelData.MiscelData[1].y;
				material.push_back(temp);

				pConst->Create(material.size() * sizeof(DirectX::XMFLOAT4), material.data(), 1u);
				//pShader->UploadFloat4(material, false, 1);
			}

		}

		auto vertexData = GetVec(matVec);
		vConst->Create(vertexData.size() * sizeof(DirectX::XMFLOAT4), vertexData.data(), 0u);
	}

	void RenderQueue::submit(std::string ModelPath, ModelProperties ModelProp)
	{
		//Check if the map contains the model path
		if (Models.contains(ModelPath))
		{
			//Increase the count 
			Models[ModelPath].count++;
		}
		else
		{
			Ref<Model> model = CreateRef<Model>(ModelPath);
			ModelData data;
			data.vbuf = model->Meshes[0].vBuf;
			std::vector<LayoutBuffer> list;

			list.emplace_back("Position", 0u, PropertiesDataType::Float3, false, 32);
			list.emplace_back("Normal", 12u, PropertiesDataType::Float3, false, 32);
			list.emplace_back("TexCoord", 24u, PropertiesDataType::Float2, false, 32);

			data.vbuf->SetLayout(list, data.vshader);
			data.ibuf = model->Meshes[0].iBuf;
			data.vshader = ModelProp.vshader;
			data.pshader = ModelProp.pshader;
			data.count = 1;
			data.mat = GetMatrix(ModelProp);
			data.MiscelData = ModelProp.MiscelData;
			Models.insert({ ModelPath,data });
		}
	}

	
}