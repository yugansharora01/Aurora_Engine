#pragma once

#include "IndexedTriangleList.h"
#include <DirectXMath.h>
#include "Aurora/Core/AuroraMath.h"

namespace Aurora {

	class Prism
	{
	public:
		template<class V>
		static IndexedTriangleList<V> MakeTesselated(int longDiv)
		{
			namespace dx = DirectX;
			assert(longDiv >= 3);

			const auto base = dx::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
			const auto offset = dx::XMVectorSet(0.0f, 0.0f, 2.0f, 0.0f);
			const float longitudeAngle = 2.0f * PI / longDiv;

			// near center
			std::vector<V> vertices;
			vertices.emplace_back();
			vertices.back() = { 0.0f,0.0f,-1.0f };
			const auto iCenterNear = (unsigned short)(vertices.size() - 1);

			//far center
			vertices.emplace_back();
			vertices.back() = { 0.0f,0.0f,1.0f };
			const auto iCenterFar = (unsigned short)(vertices.size() - 1);

			//base vertices
			for (int iLong = 0; iLong < longDiv; iLong++)
			{
				//near base
				{
					vertices.emplace_back();
					auto v = dx::XMVector3Transform(
						base,
						dx::XMMatrixRotationZ(longitudeAngle * iLong)
					);
					dx::XMStoreFloat3(&vertices.back(), v);
				}
				//far base
				{
					vertices.emplace_back();
					auto v = dx::XMVector3Transform(
						base,
						dx::XMMatrixRotationZ(longitudeAngle * iLong)
					);
					v = dx::XMVectorAdd(v, offset);
					dx::XMStoreFloat3(&vertices.back(), v);
				}
			}

			//side indices
			std::vector<unsigned short> indices;
			for (unsigned short iLong = 0; iLong < longDiv; iLong++)
			{
				const auto i = iLong * 2;
				const auto mod = longDiv * 2;
				indices.push_back(i + 2);
				indices.push_back((i + 2) % mod + 2);
				indices.push_back(i + 1 + 2);
				indices.push_back((i + 2) % mod + 2);
				indices.push_back((i + 2) % mod + 2);
				indices.push_back(i + 1 + 2);
			}
			// base indices
			for (unsigned short iLong = 0; iLong < longDiv; iLong++)
			{
				const auto i = iLong * 2;
				const auto mod = longDiv * 2;
				indices.push_back(i + 2);
				indices.push_back(iCenterNear);
				indices.push_back((i + 2) % mod + 2);
				indices.push_back(iCenterNear);
				indices.push_back(i + 1 + 2);
				indices.push_back((i + 3) % mod + 2);
			}
			return { std::move(vertices),std::move(indices) };
		}
		template<class V>
		static IndexedTriangleList<V> Make()
		{
			return MakeTesselated<V>(24);
		}

		static BindableList Get(std::wstring vShaderPath, std::wstring pShaderPath,int faces)
		{
			BindableList b;


			const auto model = Prism::MakeTesselated<DirectX::XMFLOAT3>(faces);

			

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