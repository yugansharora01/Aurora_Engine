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

	void Component::OnComponentAdd(Entity* e)
	{
		auto list = e->GetScene()->registry->GetList();
		for (size_t i = 0; i < list.size(); i++)
		{
			if (list[i]->handle == e->handle)
			{
				this->entity = list[i];
			}
		}
	}

}

