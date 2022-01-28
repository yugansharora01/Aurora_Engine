#pragma once

#include "IndexedTriangleList.h"
#include <DirectXMath.h>
#include "Aurora/Core/AuroraMath.h"

namespace Aurora {

	class Cone
	{
	public:
		template<class V>
		static IndexedTriangleList<V> Make(int longDiv)
		{
			namespace dx = DirectX;
			assert(longDiv >= 3);

			const auto base = dx::XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f);
			const float longitudeAngle = 2.0f * PI / longDiv;

			// base vertices
			std::vector<V> vertices;
			for (int iLong = 0; iLong < longDiv; iLong++)
			{
				vertices.emplace_back();
				auto v = dx::XMVector3Transform(
					base,
					dx::XMMatrixRotationZ(longitudeAngle * iLong)
				);
				dx::XMStoreFloat3(&vertices.back(), v);
			}
			// the center
			vertices.emplace_back();
			vertices.back() = { 0.0f,0.0f,1.0f };
			const auto iCenter = (unsigned short)(vertices.size() - 1);
			// the tip :darkness:
			vertices.emplace_back();
			vertices.back() = { 0.0f,0.0f,1.0f };
			const auto iTip = (unsigned short)(vertices.size() - 1);

			//base indices
			std::vector<unsigned short> indices;
			for (unsigned short iLong = 0; iLong < longDiv; iLong++)
			{
				indices.push_back(iCenter);
				indices.push_back((iLong + 1) % longDiv);;
				indices.push_back(iLong);
			}

			//cone indices
			for (unsigned short iLong = 0; iLong < longDiv; iLong++)
			{
				indices.push_back(iLong);
				indices.push_back((iLong + 1) % longDiv);
				indices.push_back(iTip);
			}

			return { std::move(vertices),std::move(indices) };
		}
		template<class V>
		static IndexedTriangleList<V> Make()
		{
			return MakeTesselated<V>(24);
		}

		static BindableList Get(std::wstring vShaderPath, std::wstring pShaderPath, int faces)
		{
			BindableList b;


			const auto model = Cone::Make<DirectX::XMFLOAT3>(faces);



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