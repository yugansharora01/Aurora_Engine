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
		Camera = CreateRef<EditorCamera>(1, 3.0f / 4.0f, 0.5f, 40.0f);
		mat = glm::mat4(1.0f);
	}

	Ref<Entity> Scene::CreateEntity()
	{
		Ref<Entity> entity = CreateRef<Entity>(registry->CreateEntity(), this);
		registry->add(entity);
		return entity;
	}

	void Scene::DestroyEntity(Ref<Entity> entity)
	{
		registry->DestroyEntity(entity);
	}

	void Scene::Update()
	{
		auto height = Application::Get().GetWindow().GetHeight();
		auto width = Application::Get().GetWindow().GetWidth();
		Camera->UpdateProjection(1, (float)height / (float)width, 0.5f, 40.0f);

		Renderer::BeginScene();
		auto entities = registry->GetList();
		for (size_t i = 0; i < entities.size(); i++)
		{
			auto& vShader = entities[i]->GetComponent<MeshComponent>()->vShader;
			auto& pShader = entities[i]->GetComponent<MeshComponent>()->pShader;
			auto& vBuf = entities[i]->GetComponent<MeshComponent>()->vBuf;
			auto& iBuf = entities[i]->GetComponent<MeshComponent>()->iBuf;

			glm::mat4 m = GetMatrix(entities[i]);
			glm::mat4 n = Camera->GetProjection();
			glm::mat4 l = m * n;

			vShader->UploadMat4(l);

			Renderer::Submit(vShader, pShader, vBuf, iBuf);
		}
		Renderer::EndScene();
	}

	glm::mat4 Scene::GetMatrix(Ref<Entity> entity)
	{
		auto x = entity->GetComponent<TransformComponent>()->transform.x;
		auto y = entity->GetComponent<TransformComponent>()->transform.y;
		auto z = entity->GetComponent<TransformComponent>()->transform.z;
		auto v = entity->GetComponent<TransformComponent>()->transform;
		auto x1 = entity->GetComponent<TransformComponent>()->rotation.x;
		auto y1 = entity->GetComponent<TransformComponent>()->rotation.y;
		auto z1 = entity->GetComponent<TransformComponent>()->rotation.z;

		mat = glm::translate(mat, v);
		//mat = glm::rotate(mat, x1, glm::vec3(1.0f, 0.0f, 0.0f));
		//mat = glm::rotate(mat, y1, glm::vec3(0.0f, 1.0f, 0.0f));
		//mat = glm::rotate(mat, z1, glm::vec3(0.0f, 0.0f, 1.0f));
		
		DirectX::XMMATRIX l = DirectX::XMMatrixTranslation(x, y, z);

		return mat;
		//return DirectX::XMMatrixRotationRollPitchYaw(x1, y1, z1) *
			//DirectX::XMMatrixTranslation(x, y, z);
	}
	
}