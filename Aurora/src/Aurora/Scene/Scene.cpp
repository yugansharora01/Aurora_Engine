#include "pch.h"
#include "ECS.h"
#include "Scene.h"

namespace Aurora {
	Scene::Scene()
	{
		registry = CreateRef<Registry>();
	}

	Entity Scene::CreateEntity()
	{
		Entity entity(registry->CreateEntity(),this);
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		registry->DestroyEntity(entity);
	}

	
	
}