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
		Scene(Scene& other) = default;

		Ref<Entity> CreateEntityWithUUID(UUID& id,std::string Name = "");
		Ref<Entity> CreateEntity(std::string Name = "");
		Ref<Entity> CreateChildEntityWithUUID(UUID& id,Ref<Entity> Parent,std::string Name = "");
		Ref<Entity> CreateChildEntity(Ref<Entity> Parent,std::string Name = "");
		void DestroyEntity(Ref<Entity> entity);
		void Update(Ref<EditorCamera> Editorcamera, viewportInfo viewport);

		DirectX::XMMATRIX GetMatrix(Ref<Entity> entity);
	private:
		void SubmitEntity(Ref<Entity> entity, Ref<EditorCamera> Editorcamera,DirectX::XMMATRIX ViewMat);
		std::vector<DirectX::XMFLOAT4> Light;
	};

}