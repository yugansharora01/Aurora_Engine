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

	YAML::Emitter& operator<<(YAML::Emitter& out, const DirectX::XMFLOAT4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}
	
	YAML::Emitter& operator<<(YAML::Emitter& out, const std::vector<DirectX::XMFLOAT4>& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq;
		for(auto& node : v)
			out << node << YAML::EndSeq;
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

		auto component = entity->GetComponent<MeshComponent>();
		//out << YAML::Key << "Vertex Shader";
		//out << YAML::BeginMap;
		//out << YAML::Key << "Path" << YAML::Value << component->vShader->path;
		//out << YAML::EndMap;
		//out << YAML::Key << "Pixel Shader";
		//out << YAML::BeginMap; // Pixel Shader
		//out << YAML::Key << "Path" << YAML::Value << component->vShader->path;
		//out << YAML::Key << "Data For Shader";
		//out << YAML::BeginMap; //Data For Shader
		//for (int i = 0; i < component->vShader->UploadData.size(); i++)
		//{
		//	out << YAML::Key << component->vShader->UploadData[i].name << YAML::Value << component->vShader->UploadData[i].data;
		//}
		//out << YAML::EndMap; //Data For Shader
		//out << YAML::EndMap; // Pixel Shader
		//out << YAML::Key << "Vertex Buffer" << YAML::Value << component->vShader->path;
		//out << YAML::Key << "Index Buffer" << YAML::Value << component->vShader->path;
		//

		SerializeComponent<MeshComponent>(out, entity, "MeshComponent", [](auto& out, auto& component)
		{
				out << YAML::Key << "Vertex Shader";
				out << YAML::BeginMap;
				out << YAML::Key << "Path" << YAML::Value << component->vShader->path;
				out << YAML::EndMap;
				out << YAML::Key << "Pixel Shader";
				out << YAML::BeginMap; // Pixel Shader
				out << YAML::Key << "Path" << YAML::Value << component->vShader->path;
				out << YAML::Key << "Data For Shader";
				out << YAML::BeginMap; //Data For Shader
				for (int i = 0; i < component->vShader->UploadData.size(); i++)
				{
					out << YAML::Key << component->vShader->UploadData[i].name << YAML::Value << component->vShader->UploadData[i].data;
				}
				out << YAML::EndMap; //Data For Shader
				out << YAML::EndMap; // Pixel Shader
				out << YAML::Key << "Vertex Buffer" << YAML::Value << component->vShader->path;
				out << YAML::Key << "Index Buffer" << YAML::Value << component->vShader->path;

				
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