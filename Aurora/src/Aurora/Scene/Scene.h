#pragma once
#include <DirectXMath.h>

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
		Ref<Entity> CreateEntity(std::string Name = "");
		void DestroyEntity(Ref<Entity> entity);
		void Update();

		DirectX::XMMATRIX GetMatrix(Ref<Entity> entity);
	};

}