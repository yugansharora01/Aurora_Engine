#include "pch.h"
#include "Serializer.h"

#include <yaml-cpp/yaml.h>

#include <fstream>

#include <DirectXMath.h>

namespace Aurora
{
	YAML::Emitter& operator<<(YAML::Emitter& out, const DirectX::XMFLOAT3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}


	Serializer::Serializer(Ref<Scene> scene)
		:m_scene(scene)
	{
	}

	template<typename T,typename Function>
	void SerializeComponent(YAML::Emitter& out, Ref<Entity> entity,std::string str, Function f)
	{
		if (entity->HasComponent<T>())
		{
			out << YAML::Key << str;
			out << YAML::BeginMap;

			auto component = entity->GetComponent<T>();

			f(out, component);

			out << YAML::EndMap;
		}
		
	}

	static void SerializeEntity(YAML::Emitter& out,Ref<Entity> entity)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << entity->handle;

		SerializeComponent<TagComponent>(out, entity,"TagComponent", [](auto& out, auto& component)
		{
				out << YAML::Key << "Tag" << YAML::Value << component->tag;
		});

		SerializeComponent<TransformComponent>(out, entity, "TransformComponent", [](auto& out, auto& component)
		{
				out << YAML::Key << "Transform" << YAML::Value << component->transform;
				out << YAML::Key << "Rotation" << YAML::Value << component->rotation;
				out << YAML::Key << "Scale" << YAML::Value << component->scale;
		});

		out << YAML::EndMap;
	}

	void Serializer::Serialize(std::string file)
	{
		auto list = m_scene->registry->GetList();
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << m_scene->name;
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;


		for (auto i = 0; i < list.size(); i++)
		{
			SerializeEntity(out,list[i]);
		}

		out << YAML::EndMap;
		std::ofstream fout(file);
		fout << out.c_str();
	}

	bool Serializer::Deserialize(std::string file)
	{
		return false;
	}
}