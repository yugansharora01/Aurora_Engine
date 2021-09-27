#pragma once

#include "Bindables.h"


namespace Aurora
{

	class VertexBuffer : public Bindables
	{
	public:
		virtual ~VertexBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static std::shared_ptr<VertexBuffer> Create(
			const std::vector<DirectX::XMFLOAT3>& vertices);
		
	};

	class IndexBuffer : public Bindables
	{
	public:
		virtual ~IndexBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		
		virtual const UINT GetCount() = 0;

		static std::shared_ptr<IndexBuffer> Create(
			const std::vector<unsigned short>& indices);
		

	};

	class InputLayout : public Bindables
	{
	public:
		virtual ~InputLayout() = default;

		
		static std::shared_ptr<InputLayout> Create(
			const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
			ID3DBlob* pVertexShaderBytecode);
		
	};


}
