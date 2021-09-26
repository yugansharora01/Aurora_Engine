#include "pch.h"
#include "Sheet.h"
#include "Platform/DirectX/BindableBase.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "Aurora/Drawables/Geometry/Plane.h"
#include "Platform/DirectX/Surface.h"
#include "Platform/DirectX/Texture.h"
#include "Platform/DirectX/Sampler.h"

namespace Aurora {

	Sheet::Sheet(Graphics& gfx, std::string name)
		:name(name)
	{
		namespace dx = DirectX;

		if (!IsStaticInitialized())
		{
			struct Vertex
			{
				dx::XMFLOAT3 pos;
				struct
				{
					float u;
					float v;
				}tex;
			};
			auto model = Plane::Make<Vertex>();

			model.vertices[0].tex = { 0.0f,0.0f };
			model.vertices[1].tex = { 1.0f,0.0f };
			model.vertices[2].tex = { 0.0f,1.0f };
			model.vertices[3].tex = { 1.0f,1.0f };

			//AddStaticBind(std::make_unique<Texture>(gfx, Surface::FromFile(name)));

			AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));

			AddStaticBind(std::make_unique<Sampler>(gfx));

			auto pvs = std::make_unique<VertexShader>(gfx, L"TextureVS.cso");
			auto pvsbc = pvs->GetBytecode();

			AddStaticBind(std::move(pvs));

			AddStaticBind(std::make_unique<PixelShader>(gfx, L"TexturePS.cso"));

			AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
				{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
			};
			AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));
			AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
		}
		else
		{
			SetIndexFromStatic();
		}
		SetMatrix(dx::XMMatrixTranslation(0.0f, 0.0f, 20.0f));
		AddBind(std::make_unique<TransformCbuf>(gfx, *this));
		AddBind(std::make_unique<Texture>(gfx, Surface::FromFile(name)));

	}

	void Sheet::Update(float dt) noexcept
	{
	}

	DirectX::XMMATRIX Sheet::GetTransformXM() const noexcept
	{
		return mat;
	}

	void Sheet::SetMatrix(DirectX::XMMATRIX m) noexcept
	{
		mat = m;
	}

}