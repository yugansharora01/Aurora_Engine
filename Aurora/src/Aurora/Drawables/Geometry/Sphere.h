#pragma once

#include "IndexedTriangleList.h"
#include "Aurora/Core/AuroraMath.h"

#include <DirectXMath.h>
#include <vector>

namespace Aurora {

	class Sphere
	{
	public:
		template<class V>
		static IndexedTriangleList<V> MakeTesselated(int latDiv, int longDiv)
		{
			namespace dx = DirectX;
			assert(latDiv >= 3);
			assert(longDiv >= 3);

			constexpr float radius = 1.0f;
			const auto base = dx::XMVectorSet(0.0f, 0.0f, radius, 0.0f);
			const float lattitudeAngle = PI / latDiv;
			const float longitudeAngle = 2.0f * PI / longDiv;

			std::vector<V> vertices;
			for (int iLat = 1; iLat < latDiv; iLat++)
			{
				const auto latBase = dx::XMVector3Transform(
					base,
					dx::XMMatrixRotationX(lattitudeAngle * iLat)
				);
				for (int iLong = 0; iLong < longDiv; iLong++)
				{
					vertices.emplace_back();
					auto v = dx::XMVector3Transform(
						latBase,
						dx::XMMatrixRotationZ(longitudeAngle * iLong)
					);
					dx::XMStoreFloat3(&vertices.back(), v);
				}
			}
			//add the cap vertices
			const auto iNorthPole = (unsigned short)vertices.size();
			vertices.emplace_back();
			dx::XMStoreFloat3(&vertices.back(), base);
			const auto iSouthPole = (unsigned short)vertices.size();
			vertices.emplace_back();
			dx::XMStoreFloat3(&vertices.back(), dx::XMVectorNegate(base));

			const auto calcIdx = [latDiv, longDiv](unsigned short iLat, unsigned short iLong)
			{ return iLat * longDiv + iLong; };

			std::vector<unsigned short> indices;
			for (unsigned short iLat = 0; iLat < latDiv - 2; iLat++)
			{
				for (unsigned short iLong = 0; iLong < longDiv - 1; iLong++)
				{
					indices.push_back(calcIdx(iLat, iLong));
					indices.push_back(calcIdx(iLat + 1, iLong));
					indices.push_back(calcIdx(iLat, iLong + 1));
					indices.push_back(calcIdx(iLat, iLong + 1));
					indices.push_back(calcIdx(iLat + 1, iLong));
					indices.push_back(calcIdx(iLat + 1, iLong + 1));
				}
				//wrap band
				indices.push_back(calcIdx(iLat, longDiv - 1));
				indices.push_back(calcIdx(iLat + 1, longDiv - 1));
				indices.push_back(calcIdx(iLat, 0));
				indices.push_back(calcIdx(iLat, 0));
				indices.push_back(calcIdx(iLat + 1, longDiv - 1));
				indices.push_back(calcIdx(iLat + 1, 0));
			}
			//cap fans
			for (unsigned short iLong = 0; iLong < longDiv - 1; iLong++)
			{
				//north
				indices.push_back(iNorthPole);
				indices.push_back(calcIdx(0, iLong));
				indices.push_back(calcIdx(0, iLong + 1));
				//south
				indices.push_back(calcIdx(latDiv - 2, iLong + 1));
				indices.push_back(calcIdx(latDiv - 2, iLong));
				indices.push_back(iSouthPole);
			}
			//wrap triangles
			//north
			indices.push_back(iNorthPole);
			indices.push_back(calcIdx(0, longDiv - 1));
			indices.push_back(calcIdx(0, 0));

			//South
			indices.push_back(calcIdx(latDiv - 2, 0));
			indices.push_back(calcIdx(latDiv - 2, longDiv - 1));
			indices.push_back(iSouthPole);

			return { std::move(vertices),std::move(indices) };
		}
		template<class V>
		static IndexedTriangleList<V> Make()
		{
			return MakeTesselated<V>(12, 24);
		}

		static BindableList Get(std::wstring vShaderPath, std::wstring pShaderPath, int latDiv, int longDiv)
		{
			BindableList b;

			struct Vertex
			{
				DirectX::XMFLOAT3 pos;
				DirectX::XMFLOAT3 n;
			};
			const auto model = Sphere::MakeTesselated<DirectX::XMFLOAT3>(latDiv, longDiv);

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
					{ 1.0f,1.0f,1.0f,1.0f },
					{ 1.0f,1.0f,1.0f,1.0f },
					{ 1.0f,1.0f,1.0f,1.0f },
					{ 1.0f,1.0f,1.0f,1.0f },
					{ 1.0f,1.0f,1.0f,1.0f },
					{ 1.0f,1.0f,1.0f,1.0f },
					{ 1.0f,1.0f,1.0f,1.0f },
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