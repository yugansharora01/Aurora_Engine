#pragma once

namespace Aurora {
	class Component;
	class Entity;
	class Registry;
	class Scene;

	using EntityHandle = std::size_t;
	using GroupID = std::size_t;
	constexpr std::size_t maxComponents = 32;
	constexpr std::size_t maxGroups = 32;

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

		virtual void OnComponentAdd() {}
		virtual void update() {}

		virtual ~Component() {}

	};

	class Entity
	{
	public:
		EntityHandle handle;
	public:
		Entity(EntityHandle Handle, Scene scene);

		Entity(const Entity& other) = default;

		~Entity(){}

		//Updates every component
		void Update()
		{
			for (auto& c : components)
			{
				c.update();
			}
		}

		//Deletes Entity
		void Delete()
		{
			active = false;
			//TO DO
		}

		//returns true if entity is active
		bool IsActive() const
		{
			return active;
		}

		//Checks if the Entity have the passed component
		template<typename T>
		bool HasComponent()
		{
			return componentBitSet[GetComponentTypeID<T>()];
		}

		//Adds the component to componentArray and also sets the componentBitSet 
		template<typename T,typename... Args>
		Ref<T>& AddComponent(Args&&... args)
		{
			auto c = CreateRef<T>(args...);
			c->entity = this;
			components.emplace_back(std::move(c));
			componentArray[GetComponentTypeID<T>()] = c;
			componentBitSet[GetComponentTypeID<T>()] = true;

			c->OncomponentAdd();
			return *c;
		}

		//Returns the component passed as temlate argument
		template<typename T>
		Ref<T> GetComponent() const
		{
			AU_CORE_ASSERT(HasComponent<T>(), "Entity does not have this component");
			return componentArray[GetComponentTypeID<T>()];
			
		}

		//Returns the Group with the passed GroupID
		std::vector<GroupID> GetGroup() const
		{
			return m_Groups;
		}

		//compares the Entity handle 
		bool operator==(const Entity& e)
		{
			return this->handle == e.handle;
		}

	private:
		Ref<Scene> m_scene;
		std::vector<GroupID> m_Groups;
		std::vector<Component> components;
		std::bitset<maxComponents> componentBitSet;
		std::array<Component, maxComponents> componentArray;
		bool active;
	};

	class Group
	{
	public:
		GroupID id;
	public:
		Group() = default;

		Group(GroupID ID)
			:id(ID)
		{

		}

		void add(Entity entity)
		{
			GroupOfEntities.emplace_back(entity);
		}

		void remove(Entity entity)
		{
			GroupOfEntities.erase(std::find(GroupOfEntities.begin(), GroupOfEntities.end(), entity));
		}

		GroupID GetID() const
		{
			return id;
		}

	private:
		std::vector<Entity> GroupOfEntities;
	};


	
	// Every scene will initialize a registry which will have all the entities
	class Registry
	{
	friend class Scene;

	public:
		//returns the vector of Ref<Entity>
		std::vector<Entity> GetList()
		{
			return list;
		}

		//Add the entity to the Group 
		void AddToGroup(Entity entity, GroupID group)
		{
			GroupMap[group].add(entity);
			entity.GetGroup().push_back(group);
		}

		//Removes the entity from the group
		void RemoveEntityFromGroup(Entity entity, GroupID group)
		{
			GroupMap[group].remove(entity);
		}

		//returns the vector of Ref<Entity> which contains grouped entities 
		Group GetGroup(GroupID group)
		{
			return GroupMap[group];
		}

		//Add the Entity to the list of Entities
		EntityHandle CreateEntity()
		{
			return GetNewEntityHandle();
		}

		void add(Entity e)
		{
			list.emplace_back(e);
		}

		void DestroyEntity(Entity entity)
		{
			//Remove Entity from every group
			for (size_t i = 0;i < entity.GetGroup().size();i++)
			{
				RemoveEntityFromGroup(entity, entity.GetGroup()[i]);
			}

			//Remove Entity from the list of entities 
			list.erase(std::find(list.begin(), list.end(), entity));

			//Deleting the Entity
			entity.Delete();
		}


		void GroupEntities(std::initializer_list<Entity> Entitylist)
		{
			Group newGroup(GetNewGroupID());
			for (auto e : Entitylist)
			{
				newGroup.add(e);
			}			
		}

		template<typename comp1,typename comp2,typename TypeOfComp1Field, typename TypeOfComp2Field>
		Group group(TypeOfComp1Field feild1, TypeOfComp2Field field2)
		{
			Group newGroup(GetNewGroupID());
			for (auto e : list)
			{
				if (e.HasComponent<comp1>() || e.HasComponent<comp2>())
				{
					newGroup.add(e);
				}
			}
		}

	private:
		Registry() = default;

		GroupID GetNewGroupID()
		{
			static GroupID lastID = 0;
			return lastID++;
		}

		EntityHandle GetNewEntityHandle()
		{
			static GroupID lastID = 0;
			return lastID++;
		}

	private:
		
		std::vector<Entity> list;
		std::map<GroupID, Group> GroupMap;
	};

}



