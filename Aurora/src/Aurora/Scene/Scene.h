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
	public:
		Scene();
		Scene(Scene& other)
		{
			this->registry = registry;
		}
		Ref<Entity> CreateEntity();
		void DestroyEntity(Ref<Entity> entity);
		void Update();

		DirectX::XMMATRIX GetMatrix(Ref<Entity> entity);
	};

}