#pragma once

namespace Aurora {
	class Component;
	class Entity;
	class Registry;


	constexpr std::size_t maxComponents = 32;

	inline std::size_t GetNewComponentTypeID()
	{

		//TO DO: Change the way of generating ID's

		//ID's start from 0
		static std::size_t lastID = 0u;
		return lastID++;
	}

	template<typename T>
	inline std::size_t GetComponentTypeID()
	{
		static std::size_t typeID = GetNewComponentTypeID();
		return typeID;
	}

	class Component
	{
	public:
		Ref<Entity> entity;

		virtual void init() {}
		virtual void update() {}
		virtual void draw() {}

		virtual ~Component() {}

	};

	class Entity
	{
	public:
		bool active;
		std::vector<Ref<Component>> components;
		std::bitset<maxComponents> componentBitSet;
		std::array<Ref<Component>, maxComponents> componentArray;
	public:
		Entity()
		{
			active = true;
		}

		~Entity(){}

		void Update()
		{
			for (auto& c : components)
			{
				c->update();
			}
		}

		void Draw()
		{
			for (auto& c : components)
			{
				c->draw();
			}
		}

		bool IsActive() const
		{
			return active;
		}

		template<typename T>
		bool HasComponent()
		{
			return componentBitSet[GetComponentTypeID<T>()];
		}

		template<typename T,typename... Args>
		Ref<T>& AddComponent(Args&&... args)
		{
			auto c = CreateRef<T>(args...);
			c->entity = this;
			components.emplace_back(std::move(c));
			componentArray[GetComponentTypeID<T>()] = c;
			componentBitSet[GetComponentTypeID<T>()] = true;

			c->init();
			return *c;
		}

		template<typename T>
		Ref<T> GetComponent() const
		{
			return componentArray[GetComponentTypeID<T>()];
		}
	};

	

	class Registry
	{
	public:
		Scope<Registry> GetRegistry() const
		{
			return std::move(registry);
		}
	private:
		Registry();

	private:
		static Scope<Registry> registry;
		std::map<std::string, Ref<Entity>> list;
	};

	Registry::Registry()
	{
	}


	Scope<Registry> Registry::registry = CreateScope<Registry>();
}
