#include "pch.h"
#include "Serializer.h"

#define YAML_CPP_STATIC_DEFINE

#include "include/yaml-cpp/yaml.h"

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

		for (auto i = 0; i < list.size(); i++)
		{
			SerializeEntity(list[i]);
		}
	}

	bool Serializer::Deserialize(std::string file)
	{
		return false;
	}
}