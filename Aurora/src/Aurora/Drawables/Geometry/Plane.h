#pragma once

#include <vector>
#include <array>
#include "IndexedTriangleList.h"
#include "Aurora/Core/AuroraMath.h"

namespace Aurora {

	class Plane
	{
	public:
		template<class V>
		static IndexedTriangleList<V> MakeTesselated(int divisions_x, int divisions_y)
		{
			namespace dx = DirectX;
			assert(divisions_x >= 1);
			assert(divisions_y >= 1);

			constexpr float width = 2.0f;
			constexpr float height = 2.0f;
			const int nVertices_x = divisions_x + 1;
			const int nVertices_y = divisions_y + 1;
			std::vector<V> vertices(nVertices_x * nVertices_y);

			{
				const float side_x = width / 2.0f;
				const float side_y = height / 2.0f;
				const float divisionSize_x = width / float(divisions_x);
				const float divisionSize_y = height / float(divisions_y);
				const auto bottomLeft = dx::XMVectorSet(-side_x, -side_y, 0.0f, 0.0f);

				for (int y = 0, i = 0; y < nVertices_y; y++)
				{
					const float y_pos = float(y) * divisionSize_y;
					for (int x = 0; x < nVertices_x; x++, i++)
					{
						const auto v = dx::XMVectorAdd(
							bottomLeft,
							dx::XMVectorSet(float(x) * divisionSize_x, y_pos, 0.0f, 0.0f)
						);
						dx::XMStoreFloat3(&vertices[i], v);
					}
				}
			}

			std::vector<unsigned short> indices;
			indices.reserve(sq(divisions_x * divisions_y) * 6);
			{
				const auto vxy2i = [nVertices_x](size_t x, size_t y)
				{
					return (unsigned short)(y * nVertices_x + x);
				};
				for (size_t y = 0; y < divisions_y; y++)
				{
					for (size_t x = 0; x < divisions_x; x++)
					{
						const std::array<unsigned short, 4> indexArray =
						{ vxy2i(x,y),vxy2i(x + 1,y),vxy2i(x,y + 1),vxy2i(x + 1,y + 1) };
						indices.push_back(indexArray[0]);
						indices.push_back(indexArray[2]);
						indices.push_back(indexArray[1]);
						indices.push_back(indexArray[1]);
						indices.push_back(indexArray[2]);
						indices.push_back(indexArray[3]);
					}
				}
			}

			return{ std::move(vertices),std::move(indices) };
		}
		template<class V>
		static IndexedTriangleList<V> Make()
		{
			return MakeTesselated<V>(1, 1);
		}

		static BindableList Get(std::wstring vShaderPath, std::wstring pShaderPath, int division_x, int division_y)
		{
			BindableList b;


			const auto model = Plane::MakeTesselated<DirectX::XMFLOAT3>(division_x, division_y);



			std::vector<VertexData> container;

			for (int i = 0; i < model.vertices.size(); i++)
			{
				container.emplace_back();
				container[i].pos = model.vertices[i];
			}

			/*container[0].color = { 255,255,0 };
			container[1].color = { 255,255,0 };
			container[2].color = { 255,255,0 };
			container[3].color = { 255,255,0 };
			container[4].color = { 255,255,80 };
			container[5].color = { 255,10,0 };*/

			b.vBuffer = VertexBuffer::Create(container);

			b.vShader = VertexShader::Create(vShaderPath);

			b.pShader = PixelShader::Create(pShaderPath);

			b.iBuffer = IndexBuffer::Create(model.indices);

			std::vector<DirectX::XMFLOAT4> face_colors =
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
			b.pShader->UploadFloat4(face_colors);

			std::vector<LayoutBuffer> list;

			list.emplace_back("Position", 0u, PropertiesDataType::Float3, false, 32);
			list.emplace_back("Color", 12, PropertiesDataType::Unorm, false, 8);

			b.vBuffer->SetLayout(list, b.vShader);

			b.vBuffer->SetTopology(TopologyType::Triangle_List);

			return b;
		}
	};
}