#pragma once

#include "Bindables.h"


namespace Aurora
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Uint, Uint2, Uint3, Uint4, Sint, Sint2, Sint3, Sint4, Bool
	};

	struct LayoutBuffer
	{
	public:
		std::string name;
		unsigned int offset;
		ShaderDataType type;
		bool Is_Normalised;
		int NumberOfBits;
		LayoutBuffer(std::string name, unsigned int offset, ShaderDataType type, bool Is_Normalised,int NumberOfBits)
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
		virtual ~VertexBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetData(void* data,unsigned int size) = 0;
		
		virtual void SetLayout(std::vector<LayoutBuffer> layout,std::shared_ptr<class VertexShader> vShader) = 0;
		virtual void SetTopology(TopologyType type) = 0;
		static std::shared_ptr<VertexBuffer> Create(
			const std::vector<DirectX::XMFLOAT3>& vertices);
		
	};

	class IndexBuffer
	{
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
