#include "pch.h"
#include "Melon.h"
#include "Aurora/Renderer/BindableBase.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "Aurora/Drawables/Geometry/Sphere.h"

namespace Aurora {

	Melon::Melon(Graphics& gfx, int latdistp, int longdistp)
	{
		namespace dx = DirectX;

		if (!IsStaticInitialized())
		{
			auto pvs = VertexShader::Create(L"ColorIndexVS.cso");
			auto pvsbc = pvs->GetBytecode();

			AddStaticBind(std::move(pvs));

			AddStaticBind(PixelShader::Create(L"ColorIndexPS.cso"));

			struct PixelShaderConstants
			{
				struct
				{
					float r;
					float g;
					float b;
					float a;
				}face_colors[8];
			};

			const PixelShaderConstants cb2 =
			{
				{
					{ 1.0f,1.0f,1.0f },
					{ 1.0f,0.0f,0.0f },
					{ 0.0f,1.0f,0.0f },
					{ 1.0f,1.0f,0.0f },
					{ 0.0f,0.0f,1.0f },
					{ 1.0f,0.0f,1.0f },
					{ 0.0f,1.0f,1.0f },
					{ 0.0f,0.0f,0.0f },
				}
			};
			AddStaticBind(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(cb2));


			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0}
			};
			AddStaticBind(std::make_unique<InputLayout>(ied, pvsbc));
			AddStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		}
		struct Vertex
		{
			dx::XMFLOAT3 pos;
		};
		auto model = Sphere::MakeTesselated<dx::XMFLOAT3>(latdistp, longdistp);

		//deform vertices of model by linear transformation
		model.Transform(dx::XMMatrixScaling(1.0f, 1.0f, 1.2f));
		AddBind(VertexBuffer::Create(model.vertices));
		AddIndexBuffer(IndexBuffer::Create(model.indices));

		SetMatrix(dx::XMMatrixTranslation(0.0f, 0.0f, 20.0f));

		AddBind(std::make_unique<TransformCbuf>(*this));
	}

	void Melon::Update(float dt) noexcept
	{
	}

	DirectX::XMMATRIX Melon::GetTransformXM() const noexcept
	{
		return mat;
	}

	void Melon::SetMatrix(DirectX::XMMATRIX m) noexcept
	{
		mat = m;
	}

}
