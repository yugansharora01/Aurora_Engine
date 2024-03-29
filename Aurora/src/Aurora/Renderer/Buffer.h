#pragma once

#include "Bindables.h"

#include <yaml-cpp/yaml.h>


namespace Aurora
{

	struct VertexData
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 texCoord;
		VertexData() = default;

		friend YAML::Emitter& operator<<(YAML::Emitter& out, const VertexData& d)
		{
			out << YAML::BeginMap;
			out << YAML::Key << "Position" << YAML::Flow << YAML::BeginSeq << d.pos.x << d.pos.y << d.pos.z << YAML::EndSeq;
			out << YAML::Key << "Normal" << YAML::Flow << YAML::BeginSeq << d.normal.x << d.normal.y << d.normal.z << YAML::EndSeq;
			out << YAML::Key << "Texture Coordinates" << YAML::Flow << YAML::BeginSeq << d.texCoord.x << d.texCoord.y << YAML::EndSeq;
			out << YAML::EndMap;
			return out;
		}
	};

	enum class PropertiesDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Uint, Uint2, Uint3, Uint4, Sint, Sint2, Sint3, Sint4, Bool,Unorm
	};

	struct LayoutBuffer
	{
	public:
		std::string name;
		unsigned int offset;
		PropertiesDataType type;
		bool Is_Normalised;
		int NumberOfBits;
		LayoutBuffer() = default;
		LayoutBuffer(std::string name, unsigned int offset, PropertiesDataType type, bool Is_Normalised,int NumberOfBits)
			:name(name),offset(offset),type(type),Is_Normalised(Is_Normalised),NumberOfBits(NumberOfBits){}
	};

	enum class TopologyType
	{
		Point_List = 0,
		Line_List,
		Line_Strip,
		Triangle_List,
		Triangle_Strip
	};

	class VertexBuffer
	{
	public:
		std::vector<LayoutBuffer> Layouts;
		TopologyType Topologytype;
		std::vector<VertexData> Vertexdata;
	public:
		virtual ~VertexBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetData(void* data,unsigned int size) = 0;
		
		virtual void SetLayout(std::vector<LayoutBuffer> layout,std::shared_ptr<class Shader> vShader) = 0;
		virtual void SetTopology(TopologyType type) = 0;
		static std::shared_ptr<VertexBuffer> Create(
			const std::vector<VertexData>& vertices);
		
	};

	class IndexBuffer
	{
	public:
		std::vector<unsigned short> Indices;
	public:
		virtual ~IndexBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		//virtual void Update() = 0;
		
		virtual UINT GetCount() const noexcept = 0;

		static std::shared_ptr<IndexBuffer> Create(
			const std::vector<unsigned short>& indices);
		

	};

	class InputLayout
	{
	public:
		virtual ~InputLayout() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		//virtual void Update() = 0;
		
		static std::shared_ptr<InputLayout> Create(
			const std::vector<LayoutBuffer>& layout,
			ID3DBlob* pVertexShaderBytecode);
		
	};

	class Topology
	{

	public:
		virtual ~Topology() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		//virtual void Update() = 0;

		static std::shared_ptr<Topology> Create(TopologyType Type);
	};
}
