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
		DirectX::XMFLOAT4 LightConstants;

		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities[i]->HasComponent<LightComponent>())
			{
				Light.emplace_back(
					entities[i]->GetComponent<TransformComponent>()->translate.x, 
					entities[i]->GetComponent<TransformComponent>()->translate.y, 
					entities[i]->GetComponent<TransformComponent>()->translate.z,
					0.0f
				);
				LightConstants.x = entities[i]->GetComponent<MeshComponent>()->diffuseIntensity;
				LightConstants.y = entities[i]->GetComponent<LightComponent>()->attConst;
				LightConstants.z = entities[i]->GetComponent<LightComponent>()->attLin;
				LightConstants.w = entities[i]->GetComponent<LightComponent>()->attQuad;
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


				auto ViewMat = DirectX::XMMatrixInverse(NULL, Editorcamera->GetTransform());

				std::vector<DirectX::XMMATRIX> mat;

				

				if (pShader->path == "../Aurora/src/Aurora/Shaders/ColorIndexPS.hlsl")
				{
					pShader->UploadFloat4(pShader->UploadedData[0], false,0);
					mat.push_back(DirectX::XMMatrixTranspose(
						GetMatrix(entities[i]) * ViewMat * Editorcamera->GetProjection()));
				}
				else
				{
					Light.push_back(entities[i]->GetComponent<MeshComponent>()->color);
					Light.push_back(entities[i]->GetComponent<MeshComponent>()->diffuseColor);

					Light.push_back(LightConstants);

					pShader->UploadFloat4(Light, false);
					mat.push_back(DirectX::XMMatrixTranspose(GetMatrix(entities[i]) * ViewMat));
					mat.push_back(DirectX::XMMatrixTranspose(
						GetMatrix(entities[i]) * ViewMat * Editorcamera->GetProjection()));

					Light.pop_back();
					Light.pop_back();
					Light.pop_back();
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