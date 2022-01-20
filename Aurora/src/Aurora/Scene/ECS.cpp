#include "pch.h"
#include "ECS.h"
#include "Scene.h"
#include "Components.h"

namespace Aurora {
	Entity::Entity(EntityHandle Handle, Ref<Scene> scene)
		:handle(Handle),m_scene(scene)
	{
	}

	UUID Entity::GetUUID()
	{
		return GetComponent<IDComponent>()->ID;
	}

}

