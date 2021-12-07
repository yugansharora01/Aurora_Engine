#pragma once

#include <vector>
#include <DirectXMath.h>
#include "Aurora/Renderer/BindableBase.h"

namespace Aurora {

	struct BindableList 
	{
		Ref<VertexShader> vShader;
		Ref<PixelShader> pShader;
		Ref<VertexBuffer> vBuffer;
		Ref<IndexBuffer> iBuffer;

		BindableList() = default;

		BindableList(
			Ref<VertexShader> VertexShader,
			Ref<PixelShader> PixelShader,
			Ref<VertexBuffer> VertexBuffer,
			Ref<IndexBuffer> IndexBuffer
		)
			:vShader(VertexShader), pShader(PixelShader), vBuffer(VertexBuffer), iBuffer(IndexBuffer)
		{

		}
	};

	template<class T>
	class IndexedTriangleList
	{
	public:
		IndexedTriangleList() = default;
		IndexedTriangleList(std::vector<T> verts_in, std::vector<unsigned short> indices_in)
			:
			vertices(std::move(verts_in)),
			indices(std::move(indices_in))
		{
			assert(vertices.size() > 2);
			assert(indices.size() % 3 == 0);
		}
		void Transform(DirectX::FXMMATRIX matrix)
		{
			for (auto& v : vertices)
			{
				const DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&v.pos);
				DirectX::XMStoreFloat3(
					&v.pos,
					DirectX::XMVector3Transform(pos, matrix)
				);
			}
		}
	public:
		std::vector<T> vertices;
		std::vector<unsigned short> indices;
	};
}