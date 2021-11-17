#include "pch.h"
#include "ECS.h"
#include "Scene.h"

namespace Aurora {
	Entity::Entity(EntityHandle Handle, Scene* scene)
		:handle(Handle),m_scene(scene)
	{
		m_scene->registry->add(*this);
	}

}

