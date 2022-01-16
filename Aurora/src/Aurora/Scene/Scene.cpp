#include "pch.h"
#include "ECS.h"
#include "Scene.h"
#include "Components.h"
#include "Aurora/Renderer/Renderer.h"
#include "Aurora/Renderer/EditorCamera.h"
#include "Aurora/Application.h"
#include "Aurora/Core/Input.h"

#include "imgui.h"

namespace Aurora {
	struct EntityID
	{
		float id;
	};

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

	Scene::Scene()
	{
		registry = CreateRef<Registry>();
		name = "Untitled";
	}

	Scene::Scene(std::string name)
		:name(name)
	{
		registry = CreateRef<Registry>();
	}

	Ref<Entity> Scene::CreateEntityWithUUID(UUID& id, std::string Name)
	{

		Ref<Entity> entity = CreateRef<Entity>(registry->CreateEntity(), this);
		registry->add(entity);

		if (Name == "")
			Name = "UnNamed";

		entity->AddComponent<IDComponent>(id);
		entity->AddComponent<TagComponent>(Name);
		return entity;
	}

	Ref<Entity> Scene::CreateEntity(std::string Name)
	{
		auto id = UUID();
		return CreateEntityWithUUID(id,Name);
	}

	void Scene::DestroyEntity(Ref<Entity> entity)
	{
		registry->DestroyEntity(entity);
	}

	void Scene::Update(Ref<EditorCamera> Editorcamera, viewportInfo viewport)
	{
		auto height = Application::Get().GetWindow().GetHeight();
		auto width = Application::Get().GetWindow().GetWidth();
		Editorcamera->UpdateProjection( 1, (float)height/ (float)width, 0.5f, 40.0f);
		static bool click = false;

		Renderer::BeginScene();
		auto entities = registry->GetList();
		std::vector<DirectX::XMFLOAT4> Light;
		
		auto ViewMat = DirectX::XMMatrixInverse(NULL, Editorcamera->GetTransform());

		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities[i]->HasComponent<LightComponent>())
			{
				DirectX::XMFLOAT4 temp;
				auto LOL = DirectX::XMLoadFloat3(&entities[i]->GetComponent<TransformComponent>()->translate);
				DirectX::XMStoreFloat4(&temp, DirectX::XMVector4Transform(LOL, ViewMat));
				
				Light.push_back(temp);
				Light.push_back(entities[i]->GetComponent<LightComponent>()->ambient);
				Light.push_back(entities[i]->GetComponent<MeshComponent>()->color);
				DirectX::XMFLOAT4 LightConstants;
				LightConstants.x = entities[i]->GetComponent<LightComponent>()->diffuseIntensity;
				LightConstants.y = entities[i]->GetComponent<LightComponent>()->attConst;
				LightConstants.z = entities[i]->GetComponent<LightComponent>()->attLin;
				LightConstants.w = entities[i]->GetComponent<LightComponent>()->attQuad;
				Light.push_back(LightConstants);
			}
		}

		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities[i]->HasComponent<MeshComponent>())
			{
				auto& vShader = entities[i]->GetComponent<MeshComponent>()->vShader;
				auto& pShader = entities[i]->GetComponent<MeshComponent>()->pShader;
				auto& vBuf = entities[i]->GetComponent<MeshComponent>()->vBuf;
				auto& iBuf = entities[i]->GetComponent<MeshComponent>()->iBuf;

				vShader->UploadedData.clear();
				vShader->Refresh();
				pShader->Refresh();


				

				std::vector<DirectX::XMMATRIX> mat;

				if (pShader->path == "../Aurora/src/Aurora/Shaders/ColorIndexPS.hlsl")
				{
					pShader->UploadFloat4(pShader->UploadedData[0], false,0);
					mat.push_back(DirectX::XMMatrixTranspose(
						GetMatrix(entities[i]) * ViewMat * Editorcamera->GetProjection()));
				}
				else
				{
					if (pShader->path == "../Aurora/src/Aurora/Shaders/SolidPS.hlsl")
					{
						std::vector<DirectX::XMFLOAT4> color;
						color.push_back(entities[i]->GetComponent<MeshComponent>()->color);
						pShader->UploadFloat4(color, false, 0);
						mat.push_back(DirectX::XMMatrixTranspose(
							GetMatrix(entities[i]) * ViewMat * Editorcamera->GetProjection()));
					}
					else {
						pShader->UploadFloat4(Light, false, 0);
						mat.push_back(DirectX::XMMatrixTranspose(GetMatrix(entities[i]) * ViewMat));
						mat.push_back(DirectX::XMMatrixTranspose(
							GetMatrix(entities[i]) * ViewMat * Editorcamera->GetProjection()));


						std::vector<DirectX::XMFLOAT4> material;
						material.push_back(entities[i]->GetComponent<MeshComponent>()->color);
						DirectX::XMFLOAT4 temp;
						temp.x = entities[i]->GetComponent<MeshComponent>()->specularIntensity;
						temp.y = entities[i]->GetComponent<MeshComponent>()->specularPower;
						material.push_back(temp);
						pShader->UploadFloat4(material, false, 1);
					}
					
				}
				vShader->UploadFloat4(GetVec(mat));

				Renderer::Submit(vShader, pShader, vBuf, iBuf);
			}
			
		}
		Renderer::EndScene();
		
		
	}

	DirectX::XMMATRIX Scene::GetMatrix(Ref<Entity> entity)
	{
		auto translate = entity->GetComponent<TransformComponent>()->translate;
		auto rotation = entity->GetComponent<TransformComponent>()->rotation;
		auto scale = entity->GetComponent<TransformComponent>()->scale;

		DirectX::XMFLOAT4 zero(0.0f, 0.0f, 0.0f,0.0f);
		DirectX::XMFLOAT4 identity(1.0f, 0.0f, 0.0f,0.0f);
		auto zeroVec = DirectX::XMLoadFloat4(&zero);
		auto translateVec = DirectX::XMLoadFloat3(&translate);
		auto rotationVec = DirectX::XMLoadFloat3(&rotation);
		auto scaleVec = DirectX::XMLoadFloat3(&scale);
		auto identityQuat = DirectX::XMLoadFloat4(&identity);

		return DirectX::XMMatrixTransformation(zeroVec, identityQuat, scaleVec, zeroVec, DirectX::XMQuaternionRotationRollPitchYawFromVector(rotationVec), translateVec);
	}
	
}