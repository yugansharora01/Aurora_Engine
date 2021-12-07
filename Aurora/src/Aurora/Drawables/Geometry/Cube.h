#pragma once

#include "IndexedTriangleList.h"
#include <DirectXMath.h>

#include "Aurora/Renderer/BindableBase.h"


namespace Aurora {

	class Cube
	{
	public:
		template<class V>
		static IndexedTriangleList<V> Make()
		{
			namespace dx = DirectX;
			constexpr float side = 1.0f / 2.0f;

			std::vector<V> vertices(8);
			vertices[0] = { -side,-side,-side };
			vertices[1] = { side,-side,-side };
			vertices[2] = { -side,side,-side };
			vertices[3] = { side,side,-side };
			vertices[4] = { -side,-side,side };
			vertices[5] = { side,-side,side };
			vertices[6] = { -side,side,side };
			vertices[7] = { side,side,side };

			return{
				std::move(vertices),{
					0,2,1, 2,3,1,
					1,3,5, 3,7,5,
					2,6,3, 3,6,7,
					4,5,7, 4,7,6,
					0,4,2, 2,4,6,
					0,1,4, 1,5,4
				}
			};
		}
		template<class V>
		static IndexedTriangleList<V> MakeSkinned()
		{
			namespace dx = DirectX;

			constexpr float side = 1.0f / 2.0f;

			std::vector<V> vertices(14);

			vertices[0].pos = { -side,-side,-side };
			vertices[0].tex = { 2.0f / 3.0f,0.0f / 4.0f };
			vertices[1].pos = { side,-side,-side };
			vertices[1].tex = { 1.0f / 3.0f,0.0f / 4.0f };
			vertices[2].pos = { -side,side,-side };
			vertices[2].tex = { 2.0f / 3.0f,1.0f / 4.0f };
			vertices[3].pos = { side,side,-side };
			vertices[3].tex = { 1.0f / 3.0f,1.0f / 4.0f };
			vertices[4].pos = { -side,-side,side };
			vertices[4].tex = { 2.0f / 3.0f,3.0f / 4.0f };
			vertices[5].pos = { side,-side,side };
			vertices[5].tex = { 1.0f / 3.0f,3.0f / 4.0f };
			vertices[6].pos = { -side,side,side };
			vertices[6].tex = { 2.0f / 3.0f,2.0f / 4.0f };
			vertices[7].pos = { side,side,side };
			vertices[7].tex = { 1.0f / 3.0f,2.0f / 4.0f };
			vertices[8].pos = { -side,-side,-side };
			vertices[8].tex = { 2.0f / 3.0f,4.0f / 4.0f };
			vertices[9].pos = { side,-side,-side };
			vertices[9].tex = { 1.0f / 3.0f,4.0f / 4.0f };
			vertices[10].pos = { -side,-side,-side };
			vertices[10].tex = { 3.0f / 3.0f,1.0f / 4.0f };
			vertices[11].pos = { -side,-side,side };
			vertices[11].tex = { 3.0f / 3.0f,2.0f / 4.0f };
			vertices[12].pos = { side,-side,-side };
			vertices[12].tex = { 0.0f / 3.0f,1.0f / 4.0f };
			vertices[13].pos = { side,-side,side };
			vertices[13].tex = { 0.0f / 3.0f,2.0f / 4.0f };

			return{
				std::move(vertices),{
					0,2,1,   2,3,1,
					4,8,5,   5,8,9,
					2,6,3,   3,6,7,
					4,5,7,   4,7,6,
					2,10,11, 2,11,6,
					12,3,7,  12,7,13
				}
			};
		}

		static BindableList Get(std::wstring vShaderPath, std::wstring pShaderPath)
		{
			BindableList b;

			const auto model = Cube::Make<DirectX::XMFLOAT3>();

			std::vector<VertexData> container;

			for (int i = 0; i < model.vertices.size(); i++)
			{
				container.emplace_back();
				container[i].pos = model.vertices[i];
			}

			b.vBuffer = VertexBuffer::Create(container);

			b.vShader = VertexShader::Create(vShaderPath);

			b.pShader = PixelShader::Create(pShaderPath);

			b.iBuffer = IndexBuffer::Create(model.indices);

			std::array<DirectX::XMFLOAT4, 8> face_colors =
			{
				{
					{ 1.0f,1.0f,1.0f,1.0f },
					{ 1.0f,0.0f,0.0f,1.0f },
					{ 0.0f,1.0f,0.0f,1.0f },
					{ 1.0f,1.0f,0.0f,1.0f },
					{ 0.0f,0.0f,1.0f,1.0f },
					{ 1.0f,0.0f,1.0f,1.0f },
					{ 0.0f,1.0f,1.0f,1.0f },
					{ 0.0f,0.0f,0.0f,1.0f },
				}
			};
			b.pShader->UploadMat4X8(face_colors);

			std::vector<LayoutBuffer> list;

			list.emplace_back("Position", 0u, ShaderDataType::Float3, false, 32);
			list.emplace_back("Color", 12, ShaderDataType::Unorm, false, 8);

			b.vBuffer->SetLayout(list, b.vShader);

			b.vBuffer->SetTopology(TopologyType::Triangle_List);

			return b;
		}
	};
}