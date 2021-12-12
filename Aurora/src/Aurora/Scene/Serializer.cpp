#include "pch.h"
#include "Serializer.h"

#include "yaml-cpp/yaml.h"

#include <fstream>

namespace Aurora
{
	Serializer::Serializer(Ref<Scene> scene)
		:m_scene(scene)
	{
	}

	static void SerializeEntity(Ref<Entity> entity)
	{
		
	}

	void Serializer::Serialize(std::string file)
	{
		auto list = m_scene->registry->GetList();
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << m_scene->name;

		for (auto i = 0; i < list.size(); i++)
		{
			SerializeEntity(list[i]);
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