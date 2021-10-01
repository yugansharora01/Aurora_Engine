#pragma once

#include "Bindables.h"


namespace Aurora
{

	enum class TopologyType
	{
		Point_List = 0,
		Line_List,
		Line_Strip,
		Triangle_List,
		Triangle_Strip
	};

	class VertexBuffer : public Bindables
	{
	public:
		virtual ~VertexBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		//virtual void Update() = 0;

		static std::shared_ptr<VertexBuffer> Create(
			const std::vector<DirectX::XMFLOAT3>& vertices);
		
	};

	class IndexBuffer : public Bindables
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

	class InputLayout : public Bindables
	{
	public:
		virtual ~InputLayout() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		//virtual void Update() = 0;
		
		static std::shared_ptr<InputLayout> Create(
			const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
			ID3DBlob* pVertexShaderBytecode);
		
	};

	class Topology : public Bindables
	{
		
	public:
		virtual ~Topology() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		//virtual void Update() = 0;

		static std::shared_ptr<Topology> Create(TopologyType Type);
	};
}
