#include "pch.h"
#include "SkinnedBox.h"
#include "Aurora/Renderer/BindableBase.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "Aurora/Drawables/Geometry/Cube.h"
#include "Platform/DirectX/D3D11Surface.h"
#include "Platform/DirectX/D3D11Texture.h"
#include "Platform/DirectX/D3D11Sampler.h"

namespace Aurora {

	SkinnedBox::SkinnedBox(Graphics& gfx)
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
				} tex;
			};
			const auto model = Cube::MakeSkinned<Vertex>();

			AddStaticBind(std::make_unique<VertexBuffer>(model.vertices));

			AddStaticBind(std::make_unique<Texture>(Surface::FromFile("Images\\cube.png")));

			AddStaticBind(std::make_unique<Sampler>());

			auto pvs = std::make_unique<VertexShader>(L"TextureVS.cso");
			auto pvsbc = pvs->GetBytecode();
			AddStaticBind(std::move(pvs));

			AddStaticBind(std::make_unique<PixelShader>( L"TexturePS.cso"));

			AddStaticIndexBuffer(std::make_unique<IndexBuffer>(model.indices));

			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
				{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
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

	void SkinnedBox::Update(float dt) noexcept
	{

	}

	DirectX::XMMATRIX SkinnedBox::GetTransformXM() const noexcept
	{
		return mat;
	}

	void SkinnedBox::SetMatrix(DirectX::XMMATRIX m) noexcept
	{
		mat = m;
	}

}