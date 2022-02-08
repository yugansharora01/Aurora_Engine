#include "pch.h"
#include "ECS.h"
#include "Scene.h"
#include "Components.h"
#include "Aurora/Renderer/Renderer.h"
#include "Aurora/Renderer/EditorCamera.h"
#include "Aurora/Core/Application.h"
#include "Aurora/Core/Input.h"
#include "Aurora/Renderer/Texture.h"
#include "Aurora/Models/Light.h"

#include "imgui.h"

namespace Aurora {
	struct EntityID
	{
		float id;
	};

	

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
		Ref<Scene> ptr{ this };
		Ref<Entity> entity = CreateRef<Entity>(registry->CreateEntity(), ptr);
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

	Ref<Entity> Scene::CreateChildEntityWithUUID(UUID& id, Ref<Entity> Parent, std::string Name)
	{
		Ref<Scene> ptr = CreateRef<Scene>(*this);
		Ref<Scene> ptr1{this};
		Ref<Entity> entity = CreateRef<Entity>(registry->CreateEntity(), ptr1);
		entity->Parent = Parent;
		Parent->AddChild(entity);

		if (Name == "")
			Name = "UnNamed";

		entity->AddComponent<IDComponent>(id);
		entity->AddComponent<TagComponent>(Name);
		return entity;
	}

	Ref<Entity> Scene::CreateChildEntity(Ref<Entity> Parent, std::string Name)
	{
		auto id = UUID();
		return CreateChildEntityWithUUID(id,Parent, Name);
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

		Renderer::BeginScene(Editorcamera,Lights);
		auto entities = registry->GetList();
		
		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities[i]->HasComponent<MeshComponent>())
			{
				if (!entities[i]->GetComponent<MeshComponent>()->IsEmptyParent)
				{
					SubmitEntity(entities[i]);
				}
				if (entities[i]->GetChildrenList().size() != 0)
				{
					auto childrens = entities[i]->GetChildrenList();
					for (size_t j = 0; j < childrens.size(); j++)
					{
						SubmitEntity(childrens[j]);
					}

				}
			}
			if (entities[i]->HasComponent<TextComponent>())
			{
				TextData data;
				data.translate = entities[i]->GetComponent<TransformComponent>()->translate;
				data.rotation = entities[i]->GetComponent<TransformComponent>()->rotation;
				data.scale = entities[i]->GetComponent<TransformComponent>()->scale;

				Renderer::RenderText(data);
			}
		}
		Renderer::EndScene();
	}


	void Scene::AddLight(Ref<Entity> e)
	{
		auto LightComp = e->GetComponent<LightComponent>();
		auto TranformComp = e->GetComponent<TransformComponent>();
		LightInfo info;
		info.Position = TranformComp->translate;
		info.ambient = LightComp->ambient;
		info.diffuseColor = LightComp->diffuseColor;
		info.diffuseIntensity = LightComp->diffuseIntensity;
		info.attConst = LightComp->attConst;
		info.attLin = LightComp->attLin;
		info.attQuad = LightComp->attQuad;
		Light l(info);
		Lights.push_back(l);
		LightEntities.push_back(e);
	}

	void Scene::RemoveLight(Ref<Entity> e)
	{
		LightEntities.erase(std::find(LightEntities.begin(),LightEntities.end(),e));
	}

	void Scene::SubmitEntity(Ref<Entity> entity)
	{
		DrawableData prop;
		prop.ModelName = entity->GetComponent<MeshComponent>()->MeshName;

		prop.translate = entity->GetComponent<TransformComponent>()->translate;
		prop.rotation = entity->GetComponent<TransformComponent>()->rotation;
		prop.scale = entity->GetComponent<TransformComponent>()->scale;
		prop.MiscelData.push_back(entity->GetComponent<MeshComponent>()->color);
		DirectX::XMFLOAT4 f = { entity->GetComponent<MeshComponent>()->specularPower,entity->GetComponent<MeshComponent>()->specularIntensity,0.0f,0.0f };
		prop.MiscelData.push_back(f);

		Renderer::DrawModel(prop);
	}
	
}