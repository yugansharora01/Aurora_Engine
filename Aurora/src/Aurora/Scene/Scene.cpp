#include "pch.h"
#include "ECS.h"
#include "Scene.h"
#include "Components.h"
#include "Aurora/Renderer/Renderer.h"
#include "Aurora/Renderer/EditorCamera.h"
#include "Aurora/Application.h"

namespace Aurora {
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

	void Scene::Update(Ref<EditorCamera> Editorcamera)
	{
		auto height = Application::Get().GetWindow().GetHeight();
		auto width = Application::Get().GetWindow().GetWidth();
		Editorcamera->UpdateProjection(1, (float)height / (float)width, 0.5f, 40.0f);

		Renderer::BeginScene();
		auto entities = registry->GetList();
		for (size_t i = 0; i < entities.size(); i++)
		{
			auto& vShader = entities[i]->GetComponent<MeshComponent>()->vShader;
			auto& pShader = entities[i]->GetComponent<MeshComponent>()->pShader;
			auto& vBuf = entities[i]->GetComponent<MeshComponent>()->vBuf;
			auto& iBuf = entities[i]->GetComponent<MeshComponent>()->iBuf;

			vShader->UploadData.clear();
			
			auto ViewMat = DirectX::XMMatrixInverse(NULL,Editorcamera->GetTransform());

			vShader->UploadMat4(DirectX::XMMatrixTranspose(
				GetMatrix(entities[i]) * ViewMat * Editorcamera->GetProjection()));

			Renderer::Submit(vShader, pShader, vBuf, iBuf);

		}
		Renderer::EndScene();
	}

	DirectX::XMMATRIX Scene::GetMatrix(Ref<Entity> entity)
	{
		auto translate = entity->GetComponent<TransformComponent>()->translate;
		auto rotation = entity->GetComponent<TransformComponent>()->rotation;
		auto scale = entity->GetComponent<TransformComponent>()->scale;
		auto x = translate.x;
		auto y = translate.y;
		auto z = translate.z;
		auto x1 = rotation.x;
		auto y1 = rotation.y;
		auto z1 = rotation.z;
		auto x2 = scale.x;
		auto y2 = scale.y;
		auto z2 = scale.z;

		DirectX::XMFLOAT3 identity(1.0f, 1.0f, 1.0f);
		auto translateVec = DirectX::XMLoadFloat3(&translate);
		auto rotationVec = DirectX::XMLoadFloat3(&rotation);
		auto scaleVec = DirectX::XMLoadFloat3(&scale);
		auto identityVec = DirectX::XMLoadFloat3(&identity);

		auto mat = DirectX::XMMatrixTransformation(translateVec, identityVec, scaleVec, translateVec, rotationVec, translateVec);

		mat = DirectX::XMMatrixRotationRollPitchYaw(x1, y1, z1) *
			DirectX::XMMatrixTranslation(x, y, z) *
			DirectX::XMMatrixScaling(x2,y2,z2);

		return mat;
	}
	
}