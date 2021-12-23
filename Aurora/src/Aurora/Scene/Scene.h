#pragma once
#include <DirectXMath.h>
#include "Aurora/Scene/ECS.h"

namespace Aurora {

	class Entity;
	class Registry;
	class EditorCamera;

	class Scene
	{
	public:
		Ref<Registry> registry;
		Ref<EditorCamera> Camera;
		std::string name;
	public:
		Scene();
		Scene(std::string name);
		Scene(Scene& other)
		{
			this->registry = registry;
		}
		Ref<Entity> CreateEntity(std::string Name = "",EntityHandle handle = NULL);
		void DestroyEntity(Ref<Entity> entity);
		void Update();

		DirectX::XMMATRIX GetMatrix(Ref<Entity> entity);
	};

}