#include "pch.h"
#include "Serializer.h"
#include "Aurora/Utils/Convertors.h"

#include <yaml-cpp/yaml.h>

#include <fstream>

#include <DirectXMath.h>

namespace YAML 
{
	template<>
	struct convert<DirectX::XMFLOAT3>
	{
		static Node encode(DirectX::XMFLOAT3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, DirectX::XMFLOAT3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<DirectX::XMFLOAT4>
	{
		static Node encode(const DirectX::XMFLOAT4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, DirectX::XMFLOAT4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

	template<>
	struct convert<std::wstring>
	{
		static Node encode(std::wstring& rhs)
		{
			Node node;
			std::string p = Aurora::ws2s(rhs);
			node.push_back(p);
			return node;
		}

		static bool decode(const Node& node, std::wstring& rhs)
		{
			rhs = Aurora::s2ws(node.as<std::string>());
			return true;
		}
	};
}

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
		std::string str;
		out << YAML::BeginSeq;
		for (auto i = 0;i < v.size();i++)
		{
			out << v[i];
		}
		out << YAML::EndSeq;
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

		SerializeComponent<TagComponent>(out, entity,"TagComponent", [](YAML::Emitter& out, Ref<TagComponent>& component)
		{
			out << YAML::Key << "Tag" << YAML::Value << component->tag;
		});

		SerializeComponent<TransformComponent>(out, entity, "TransformComponent", [](YAML::Emitter& out, Ref<TransformComponent>& component)
		{
			out << YAML::Key << "Transform" << YAML::Value << component->transform;
			out << YAML::Key << "Rotation" << YAML::Value << component->rotation;
			out << YAML::Key << "Scale" << YAML::Value << component->scale;
		});

		
		SerializeComponent<MeshComponent>(out, entity, "MeshComponent", [](YAML::Emitter& out, Ref<MeshComponent>& component)
		{
			std::string str;

			out << YAML::Key << "Vertex Shader";
			out << YAML::BeginMap; //Vertex Shader
			out << YAML::Key << "Path" << YAML::Value << component->vShader->path;
			out << YAML::Key << "Data for Shader";
			out << YAML::BeginMap; //Data For Shader
			for (int i = 0; i < component->vShader->UploadData.size(); i++)
			{
				out << YAML::Key << "Size" << YAML::Value << component->vShader->UploadData[i].size();
				out << YAML::Key << "Data" << component->vShader->UploadData[i];
			}
			out << YAML::EndMap; //Data For Shader
			out << YAML::EndMap; //Vertex Shader

			out << YAML::Key << "Pixel Shader";
			out << YAML::BeginMap; // Pixel Shader
			out << YAML::Key << "Path" << YAML::Value << component->pShader->path;
			out << YAML::Key << "Data for Shader";
			out << YAML::BeginMap; //Data For Shader
			for (int i = 0; i < component->pShader->UploadData.size(); i++)
			{
				out << YAML::Key << "Size" << YAML::Value << component->pShader->UploadData[i].size();
				out << YAML::Key << "Data" << component->pShader->UploadData[i];
			}
			out << YAML::EndMap; //Data For Shader
			out << YAML::EndMap; // Pixel Shader

			out << YAML::Key << "Vertex Buffer" << YAML::Value << YAML::BeginMap; // Vertex Buffer
			out << YAML::Key << "Vertex Data" << YAML::BeginMap; // Vertex Data
			for (auto i = 0; i < component->vBuf->Vertexdata.size(); i++)
			{
				out << YAML::Key << i << YAML::Value << component->vBuf->Vertexdata[i];
			}
			out << YAML::EndMap;  // Vertex Data
			out << YAML::Key << "Topology" << YAML::Value << static_cast<int>(component->vBuf->Topologytype);
			out << YAML::Key << "Layout" << YAML::Value;
			out << YAML::BeginMap;
			for (auto i = 0; i < component->vBuf->Layouts.size(); i++)
			{
				auto& layout = component->vBuf->Layouts[i];
				out << YAML::Key << i << YAML::Value << YAML::Flow;
				out << YAML::BeginSeq << layout.name << layout.offset << static_cast<int>(layout.type) << layout.Is_Normalised << layout.NumberOfBits;
				out << YAML::EndSeq;
			}
			out << YAML::EndMap;
			out << YAML::EndMap; // Vertex Buffer

			out << YAML::Key << "Index Buffer" ;
			out << YAML::BeginMap; //index Buffer
			out << YAML::Key << "Indices" << YAML::Flow << YAML::BeginSeq;
			for (auto& node : component->iBuf->Indices)
			{
				out << node;
			}
			out << YAML::EndSeq;
			out << YAML::EndMap; //index Buffer

				
		});

		out << YAML::EndMap;
	}

	void Serializer::Serialize()
	{
		std::string path = "assets/scene/";

		std::string FinalPath = path + m_scene->name + ".Aurora";

		Serialize(FinalPath);
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

	bool Serializer::Deserialize()
	{
		return false;
	}

	bool Serializer::Deserialize(std::string file)
	{
		YAML::Node data;
		try
		{
			data = YAML::LoadFile(file);
		}
		catch (const YAML::ParserException&)
		{
			return false;
		}

		if (!data["Scene"])
			return false;

		std::string SceneName = data["Scene"].as<std::string>();
		m_scene->name = SceneName;
		AU_CORE_TRACE("Deserializing Scene {0}", SceneName);

		auto entities = data["Entities"];

		if (entities)
		{
			for (auto entity : entities)
			{
				EntityHandle handle = entity["Entity"].as<EntityHandle>();

				std::string name;
				auto tagComponent = entity["TagComponent"];
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();

				AU_CORE_TRACE("Deserialized Entity with id = {0} and name = {1}", handle, name);

				Ref<Entity> deserializedEntity = m_scene->CreateEntity(name,handle);

				auto transformComponent = entity["TransformComponent"];

				if (transformComponent)
				{
					auto component = deserializedEntity->AddComponent<TransformComponent>();

					component->transform = transformComponent["Transform"].as<DirectX::XMFLOAT3>();
					component->rotation = transformComponent["Rotation"].as<DirectX::XMFLOAT3>();
					component->scale = transformComponent["Scale"].as<DirectX::XMFLOAT3>();

				}

				auto meshComponent = entity["MeshComponent"];

				if (meshComponent)
				{
					
					auto vetexshader = meshComponent["Vertex Shader"];
					std::wstring path = vetexshader["Path"].as<std::wstring>();

					auto vShader = VertexShader::Create(path);

					auto ShaderData = vetexshader["Data for Shader"];

					int size = ShaderData["Size"].as<int>();

					auto matrixSeq = ShaderData["Data"];

					std::vector<DirectX::XMVECTOR> DataTOPass;

					for (int i = 0;i < size; i++)
					{
						
						DirectX::XMFLOAT4 temp = matrixSeq[i].as<DirectX::XMFLOAT4>();
						DataTOPass.push_back(DirectX::XMLoadFloat4(&temp));
					}

					DirectX::XMMATRIX mat(DataTOPass[0], DataTOPass[1], DataTOPass[2], DataTOPass[3] );

					vShader->UploadMat4(mat);


					auto pixelshader = meshComponent["Pixel Shader"];
					path = pixelshader["Path"].as<std::wstring>();

					auto pShader = PixelShader::Create(path);

					ShaderData = pixelshader["Data for Shader"];

					size = ShaderData["Size"].as<int>();

					matrixSeq = ShaderData["Data"];

					std::array<DirectX::XMFLOAT4,8> Mat;

					for (int i = 0; i < size; i++)
					{
						Mat[i] = matrixSeq[i].as<DirectX::XMFLOAT4>();
					}

					pShader->UploadMat4X8(Mat);

					auto vertexbuffer = meshComponent["Vertex Buffer"];
					auto vertexdata = vertexbuffer["Vertex Data"];

					std::vector<VertexData> vertices;

					for (auto i = 0;i <  vertexdata.size();i++)
					{
						VertexData d;						

						d.pos = vertexdata[i]["Position"].as<DirectX::XMFLOAT3>();
						d.color = VertexData::Color(0, 0, 0, 0);
						vertices.push_back(d);
					}

					auto vBuf = VertexBuffer::Create(vertices);

					vBuf->SetTopology((TopologyType)vertexbuffer["Topology"].as<int>());

					auto layout = vertexbuffer["Layout"];
					std::vector<LayoutBuffer> layouts;
					for (auto i = 0;i < layout.size();i++)
					{
						auto lay = layout[i];
						LayoutBuffer l;
						l.name =  lay[0].as<std::string>();
						l.offset =  lay[1].as<unsigned int>();
						l.type =  (ShaderDataType)lay[2].as<int>();
						l.Is_Normalised =  lay[3].as<bool>();
						l.NumberOfBits =  lay[4].as<int>();

						layouts.push_back(l);
					}

					vBuf->SetLayout(layouts, vShader);

					auto indexbuffer = meshComponent["Index Buffer"];

					std::vector<unsigned short> Indices;

					auto indices = indexbuffer["Indices"];

					for (auto i = 0;i<indices.size(); i++)
					{
						Indices.push_back(indices[i].as<unsigned short>());

					}

					auto iBuf = IndexBuffer::Create(Indices);

					auto component = deserializedEntity->AddComponent<MeshComponent>(vShader,pShader,vBuf,iBuf);

				}
			}
		}
		return false;
	}
}