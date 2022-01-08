#pragma once
#include <DirectXMath.h>
#include "Aurora/Scene/ECS.h"

namespace Aurora {

	struct viewportInfo
	{
		DirectX::XMFLOAT2 viewportSize;
		DirectX::XMFLOAT2 viewportPos;
		
	};

	class Entity;
	class Registry;
	class EditorCamera;

	class Scene
	{
	public:
		Ref<Registry> registry;
		std::string name;
	public:
		Scene();
		Scene(std::string name);
		Scene(Scene& other)
		{
			this->registry = registry;
		}
		Ref<Entity> CreateEntityWithUUID(UUID& id,std::string Name = "");
		Ref<Entity> CreateEntity(std::string Name = "");
		void DestroyEntity(Ref<Entity> entity);
		void Update(Ref<EditorCamera> Editorcamera, viewportInfo viewport);

		DirectX::XMMATRIX GetMatrix(Ref<Entity> entity);
	};

}