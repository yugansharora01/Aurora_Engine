#include "pch.h"
#include "Pyramid.h"
#include "Aurora/Renderer/BindableBase.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "Aurora/Drawables/Geometry/Cone.h"

namespace Aurora {

	Pyramid::Pyramid(Graphics& gfx)
	{
		namespace dx = DirectX;

		if (!IsStaticInitialized())
		{
			struct Vertex
			{
				dx::XMFLOAT3 pos;
				struct
				{
					unsigned char r;
					unsigned char g;
					unsigned char b;
					unsigned char a;
				}color;
			};
			auto model = Cone::Make<Vertex>(4);

			//set Vertex Color for mesh
			model.vertices[0].color = { 255,255,0 };
			model.vertices[1].color = { 255,255,0 };
			model.vertices[2].color = { 255,255,0 };
			model.vertices[3].color = { 255,255,0 };
			model.vertices[4].color = { 255,255,80 };
			model.vertices[5].color = { 255,10,0 };

			// deform mesh linearly
			model.Transform(dx::XMMatrixScaling(1.0f, 1.0f, 0.7f));

			AddStaticBind(std::make_unique<VertexBuffer>(model.vertices));

			auto pvs = std::make_unique<VertexShader>(L"ColorBlendVS.cso");
			auto pvsbc = pvs->GetBytecode();

			AddStaticBind(std::move(pvs));

			AddStaticBind(std::make_unique<PixelShader>(L"ColorBlendPS.cso"));

			AddStaticIndexBuffer(std::make_unique<IndexBuffer>( model.indices));

			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
				{"Color",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
			};
			AddStaticBind(std::make_unique<InputLayout>(ied, pvsbc));
			AddStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
		}
		else
		{
			SetIndexFromStatic();
		}
		SetMatrix(dx::XMMatrixTranslation(0.0f, 0.0f, 20.0f));
		AddBind(std::make_unique<TransformCbuf>(*this));
	}


	void Pyramid::Update(float dt) noexcept
	{
	}

	DirectX::XMMATRIX Pyramid::GetTransformXM() const noexcept
	{
		return mat;
	}

	void Pyramid::SetMatrix(DirectX::XMMATRIX m) noexcept
	{
		mat = m;
	}

}