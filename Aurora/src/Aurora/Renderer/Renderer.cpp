#include "pch.h"
#include "Renderer.h"
#include "Aurora/Core/Application.h"
#include "Aurora/Core/Window.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Aurora/Utils/FileOperations.h"
#include "Aurora/Models/Light.h"
#include "Aurora/Renderer/EditorCamera.h"
#include "Platform/DirectX/D3D11Buffers.h"

namespace Aurora 
{
	std::vector<std::string> Renderer::ModelPaths;
	RenderQueue Renderer::s_queue;
	bool Renderer::hasLights = false;
	std::vector<DirectX::XMFLOAT4> Renderer::data;
	Ref<D3D11PixelConstantBuffer> Renderer::pConst = CreateRef<D3D11PixelConstantBuffer>();
	Ref<D3D11VertexConstantBuffer> Renderer::vConst = CreateRef<D3D11VertexConstantBuffer>();
	DirectX::XMMATRIX Renderer::ViewMat;
	DirectX::XMMATRIX Renderer::ProjMat;
	ShaderManager Renderer::Manager;
	std::map<std::string, Ref<Texture>> ModelTexture::Textures;

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

	DirectX::XMMATRIX GetMatrix(DrawableData ModelProp)
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
		std::string TexturePath = FilesManager::GetPath(tex, PathType::ModelPath);
		TextureNames.insert({ type,TexturePath });
		if (!Textures.contains(TexturePath))
		{
			Ref<Texture> t = Texture::Create(TexturePath);
			Textures.insert({ TexturePath,t });
		}
		
	}

	void ModelTexture::AddTexture(Ref<Texture> texture, std::string identifier)
	{
		Textures.insert({ identifier,texture });
	}

	bool ModelTexture::HaveTex(TextureType type)
	{
		return Textures.contains(TextureNames[type]);
	}

	std::string ModelTexture::GetTexPath(TextureType type)
	{
		return TextureNames[type];
	}

	Ref<Texture> ModelTexture::GetTex(TextureType type)
	{
		//Check if it exists
		return Textures[TextureNames[type]];
	}
	
	Ref<Texture> ModelTexture::GetTex(std::string identifier)
	{
		//Check if it exists
		return Textures[identifier];
	}

	void Renderer::Init()
	{
		Manager.AddShader("PhongVSTextured.hlsl", "PhongTexturedVS",Shader::VertexShader);
		Manager.AddShader("PhongPSTextured.hlsl", "PhongTexturedPS",Shader::PixelShader);
		
		Manager.AddShader("TexturedVS.hlsl", "TexturedVS",Shader::VertexShader);
		Manager.AddShader("TexturedPS.hlsl", "TexturedPS",Shader::PixelShader);
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
			SetData(l);
			Bind(l);
			
			gfx->DrawIndexed(l.ibuf->GetCount());
		}
		s_queue.Models.clear();
	}


	void Renderer::DrawModel(DrawableData ModelProp)
	{
		if (!ModelProp.UsePassedShaders)
		{
			if (!data.empty())
			{
				//Has Lights
				
				ModelProp.vshader = Manager.GetShader("PhongTexturedVS");
				ModelProp.pshader = Manager.GetShader("PhongTexturedPS");
				
			}
		}
		if (!ModelProp.ModelName.empty())
		{
			ModelProp.ModelPath = FilesManager::GetPath(ModelProp.ModelName, PathType::ModelPath);
		}
		s_queue.submit(ModelProp);
	}

	void Renderer::RenderText(TextData textdata)
	{
		DrawableData d;
		d.vshader = Manager.GetShader("TexturedVS");
		d.pshader = Manager.GetShader("TexturedPS");
		s_queue.SubmitText(textdata, d);
	}

	void Renderer::Bind(DrawableData modelData)
	{
		pConst->Bind();
		vConst->Bind();
		modelData.vbuf->Bind();
		modelData.vshader->Bind();
		modelData.pshader->Bind();
		modelData.ibuf->Bind();
		if (modelData.Textures.HaveTex(ModelTexture::Albedo))
		{
			auto& str = modelData.Textures.TextureNames[ModelTexture::Albedo];
			modelData.Textures.Textures[str]->Bind();
		}
	}

	void Renderer::SetData(DrawableData modelData)
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

	void RenderQueue::submit(DrawableData ModelProp)
	{
		if (!ModelProp.ModelName.empty())
		{
			SubmitModel(ModelProp);
		}
		else
		{
			std::vector<LayoutBuffer> list;

			list.emplace_back("Position", 0u, PropertiesDataType::Float3, false, 32);
			list.emplace_back("Normal", 12u, PropertiesDataType::Float3, false, 32);
			list.emplace_back("TexCoord", 24u, PropertiesDataType::Float2, false, 32);

			ModelProp.vbuf->SetLayout(list, ModelProp.vshader);
			ModelProp.count = 1;
			ModelProp.mat = GetMatrix(ModelProp);
			Models.insert({ ModelProp.ModelPath,ModelProp });
		}
		
	}

	void RenderQueue::SubmitModel(DrawableData ModelProp)
	{
		Ref<Model> model;
		//Check if the map contains the model path
		if (AllModels.contains(ModelProp.ModelPath))
		{
			if (Models.contains(ModelProp.ModelPath))
			{
				//Increase the count 
				Models[ModelProp.ModelPath].count++;
				//------------------------------------------------------------------
				// TO DO : Provide Data Per Instance
				//------------------------------------------------------------------
				return;
			}
			else
			{
				model = AllModels[ModelProp.ModelPath];
			}

		}
		else
		{
			model = CreateRef<Model>(ModelProp.ModelPath, true);

			AllModels.insert({ ModelProp.ModelPath ,model });
		}
		ModelProp.vbuf = model->Meshes[0].vBuf;
		std::vector<LayoutBuffer> list;

		list.emplace_back("Position", 0u, PropertiesDataType::Float3, false, 32);
		list.emplace_back("Normal", 12u, PropertiesDataType::Float3, false, 32);
		list.emplace_back("TexCoord", 24u, PropertiesDataType::Float2, false, 32);

		ModelProp.vbuf->SetLayout(list, ModelProp.vshader);
		ModelProp.ibuf = model->Meshes[0].iBuf;
		ModelProp.count = 1;
		ModelProp.mat = GetMatrix(ModelProp);
		ModelProp.Textures.AddTexture(model->TexPath, ModelTexture::Albedo);
		Models.insert({ ModelProp.ModelPath,ModelProp });
	}

	void RenderQueue::SubmitText(TextData data, DrawableData Prop)
	{
		Ref<Model> model;
		if (AllModels.contains("TextContainer"))
		{
			model = AllModels["TextContainer"];
		}
		else
		{
			std::vector<VertexData> vData;

			vData.emplace_back();
			vData.emplace_back();
			vData.emplace_back();
			vData.emplace_back();
			vData[0].pos = { -1.0f,-1.0f,0.0f };
			vData[1].pos = { 1.0f,-1.0f,0.0f };
			vData[2].pos = { -1.0f, 1.0f,0.0f };
			vData[3].pos = { 1.0f, 1.0f,0.0f };

			vData[0].texCoord = { -1.0f,-1.0f };
			vData[1].texCoord = { 1.0f,-1.0f };
			vData[2].texCoord = { -1.0f, 1.0f };
			vData[3].texCoord = { 1.0f, 1.0f };

			auto vbuf = VertexBuffer::Create(vData);

			std::vector<unsigned short> iData = { 0,2,1,    2,3,1 };
			auto ibuf = IndexBuffer::Create(iData);

			std::vector<Mesh> meshes;
			meshes.emplace_back(vbuf, ibuf);

			model = CreateRef<Model>(meshes);
		}

		Prop.vbuf = model->Meshes[0].vBuf;
		Prop.ibuf = model->Meshes[0].iBuf;
		Prop.translate = data.translate;
		Prop.rotation = data.rotation;
		Prop.scale = data.scale;
		Prop.origin = data.origin;
		//Prop.Textures.AddTexture()

		submit(Prop);
	}

	void ShaderManager::AddShader(std::string ShaderName, std::string identifier,Shader::ShaderType type)
	{
		auto ShaderPath = FilesManager::GetPath(ShaderName, PathType::ShaderPath);
		auto shader = Shader::Create(ShaderPath,type);
		Shaders.insert({ identifier,shader });
	}


}