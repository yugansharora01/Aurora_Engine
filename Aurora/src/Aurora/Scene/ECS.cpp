#include "pch.h"
#include "ECS.h"
#include "Scene.h"
#include "Components.h"

namespace Aurora {
	Entity::Entity(EntityHandle Handle, Scene* scene)
		:handle(Handle),m_scene(scene)
	{
		//Ref<Entity> e(this);
		//m_scene->registry->add(e);
	}

	UUID Entity::GetUUID()
	{
		return GetComponent<IDComponent>()->ID;
	}

}

