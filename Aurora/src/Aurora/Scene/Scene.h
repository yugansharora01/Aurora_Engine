#pragma once

namespace Aurora {

	class Entity;
	class Registry;

	class Scene
	{
	public:
		Ref<Registry> registry;
	public:
		Scene();
		Scene(Scene& other) = default;
		Entity CreateEntity();
		void DestroyEntity(Entity entity);


	private:

	};

}