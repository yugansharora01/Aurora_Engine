#pragma once

#include "Aurora/Core/UUID.h"

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

		void AddEntity(Entity* e);
		virtual void OnComponentAdd(){}
		virtual void update() {}

		virtual ~Component() {}

	};

	class Entity
	{
	public:
		Ref<Entity> Parent;
		EntityHandle handle;
	public:
		Entity(EntityHandle Handle, Ref<Scene> scene);

		Entity(const Entity& other) = default;

		~Entity() = default;

		//Updates every component
		void Update()
		{
			for (auto& c : components)
			{
				c->update();
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
		Ref<T> AddComponent(Args&&... args)
		{
			Ref<T> c = CreateRef<T>(args...);
			
			components.emplace_back(c);
			componentArray[GetComponentTypeID<T>()] = c;
			componentBitSet[GetComponentTypeID<T>()] = true;
			c->AddEntity(this);
			c->OnComponentAdd();
			return c;
		}
		
		//Removes the component from componentArray and also sets the componentBitSet 
		template<typename T>
		void RemoveComponent()
		{
			auto comp = GetComponent<T>();
			for (size_t i = 0;i < components.size();i++)
			{
				if (comp == components[i])
				{
					components.erase(components.begin() + i);
				}
			}

			componentArray[GetComponentTypeID<T>()] = NULL;
			componentBitSet[GetComponentTypeID<T>()] = false;
			
		}

		//Returns the component passed as template argument
		template<typename T>
		Ref<T> GetComponent() const
		{
			AU_CORE_ASSERT(HasComponent<T>(), "Entity does not have this component");
			std::shared_ptr<T> RefToReturn = std::dynamic_pointer_cast<T>(componentArray[GetComponentTypeID<T>()]);
			return RefToReturn;
			
		}

		//Returns the Group with the passed GroupID
		std::vector<GroupID> GetGroup() const
		{
			return m_Groups;
		}

		//compares the Entity handle 
		bool operator==(const Entity& e)
		{
			return this->handle == e.handle && m_scene == e.m_scene;
		}

		operator uint32_t() const { return (uint32_t)handle; }

		Ref<Scene> GetScene()
		{
			return m_scene;
		}

		UUID GetUUID();

		Ref<Entity> GetParent()
		{
			return Parent;
		}

		std::vector<Ref<Entity>> GetChildrenList()
		{
			return children;
		}

		void AddChild(Ref<Entity> child)
		{
			children.push_back(child);
		}

		void RemoveChild(Ref<Entity> child)
		{
			children.erase(std::find(children.begin(), children.end(), child));
		}

	private:
		Ref<Scene> m_scene;
		std::vector<Ref<Entity>> children;
		std::vector<GroupID> m_Groups;
		std::vector<Ref<Component>> components;
		std::bitset<maxComponents> componentBitSet;
		std::array<Ref<Component>, maxComponents> componentArray;
		bool active;
	};

	class Group
	{
	public:
		Group() = default;

		Group(GroupID ID)
			:id(ID)
		{

		}

		void add(Ref<Entity> entity)
		{
			GroupOfEntities.emplace_back(entity);
		}

		void remove(Ref<Entity> entity)
		{
			GroupOfEntities.erase(std::find(GroupOfEntities.begin(), GroupOfEntities.end(), entity));
		}

		GroupID GetID() const
		{
			return id;
		}

	private:
		std::vector<Ref<Entity>> GroupOfEntities;
		GroupID id;
	};


	
	// Every scene will initialize a registry which will have all the entities
	class Registry
	{
	friend class Scene;

	public:

		Registry() = default;

		//returns the vector of Ref<Entity>
		std::vector<Ref<Entity>> GetList()
		{
			return list;
		}

		//Add the entity to the Group 
		void AddToGroup(Ref<Entity> entity, GroupID group)
		{
			GroupMap[group].add(entity);
			entity->GetGroup().push_back(group);
		}

		//Removes the entity from the group
		void RemoveEntityFromGroup(Ref<Entity> entity, GroupID group)
		{
			GroupMap[group].remove(entity);
		}

		//returns the Group which contains grouped entities 
		Group GetGroup(GroupID group)
		{
			return GroupMap[group];
		}

		//Add the Entity to the list of Entities
		EntityHandle CreateEntity()
		{
			return GetNewEntityHandle();
		}

		void add(Ref<Entity> entity)
		{
			//auto e = CreateRef<Entity>(entity);
			list.emplace_back(entity);
		}

		void DestroyEntity(Ref<Entity> entity)
		{
			//Remove Entity from every group
			for (size_t i = 0;i < entity->GetGroup().size();i++)
			{
				RemoveEntityFromGroup(entity, entity->GetGroup()[i]);
			}


			//Remove Entity from the list of entities 
			list.erase(std::find(list.begin(), list.end(), entity));

			//Deleting the Entity
			entity->Delete();
		}


		void GroupEntities(std::initializer_list<Ref<Entity>> Entitylist)
		{
			Group newGroup(GetNewGroupID());
			for (auto& e : Entitylist)
			{
				newGroup.add(e);
			}			
		}

		//should take a lambda to filter out the entities
		template<typename comp1,typename comp2>
		Group group()
		{
			Group newGroup(GetNewGroupID());
			for (auto& e : list)
			{
				if (e->HasComponent<comp1>() || e->HasComponent<comp2>())
				{
					newGroup.add(e);
				}
			}
			GroupMap.insert(newGroup.GetID(),newGroup);
			return newGroup;
		}

	private:

		GroupID GetNewGroupID()
		{
			static GroupID lastID = 0;
			return lastID++;
		}

		EntityHandle GetNewEntityHandle()
		{
			static EntityHandle lastID = 0;
			return lastID++;
		}

	private:
		
		std::vector<Ref<Entity>> list;
		std::map<GroupID, Group> GroupMap;
	};

}



