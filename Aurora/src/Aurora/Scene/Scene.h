#pragma once
#include <DirectXMath.h>
#include <glm/glm.hpp>

namespace Aurora {

	class Entity;
	class Registry;
	class EditorCamera;

	class Scene
	{
	public:
		Ref<Registry> registry;
		Ref<EditorCamera> Camera;
		glm::mat4 mat;
	public:
		Scene();
		Scene(Scene& other)
		{
			this->registry = registry;
		}
		Ref<Entity> CreateEntity();
		void DestroyEntity(Ref<Entity> entity);
		void Update();

		glm::mat4 GetMatrix(Ref<Entity> entity);
	};

}