#include "pch.h"
#include "Box.h"
#include "Aurora/Renderer/BindableBase.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "Aurora/Drawables/Geometry/Cube.h"

namespace Aurora {

	Box::Box(Graphics& gfx)
	{
		namespace dx = DirectX;

		if (!IsStaticInitialized())
		{
			struct Vertex
			{
				dx::XMFLOAT3 pos;
			};
			const auto model = Cube::Make<dx::XMFLOAT3>();

			AddStaticBind(VertexBuffer::Create(model.vertices));

			auto pvs = VertexShader::Create(L"../bin/Debug-windows-x86_64/Aurora/ColorIndexVS.cso");
			auto pvsbc = pvs->GetBytecode();

			AddStaticBind(std::move(pvs));

			AddStaticBind(PixelShader::Create(L"../bin/Debug-windows-x86_64/Aurora/ColorIndexPS.cso"));

			AddStaticIndexBuffer(IndexBuffer::Create(model.indices));

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
			AddStaticBind(InputLayout::Create(ied, pvsbc));
			AddStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
		}
		else
		{
			SetIndexFromStatic();
		}

		SetMatrix(DirectX::XMMatrixTranslation(0.0f, 0.0f, 10.0f));

		AddBind(std::make_unique<TransformCbuf>(gfx, *this));

		// model deformation transform (per instance, not stored as bind)
		dx::XMStoreFloat3x3(
			&mt,
			dx::XMMatrixScaling(1.0f, 1.0f, 1.0f)
		);
	}

	DirectX::XMMATRIX Box::GetTransformXM() const noexcept
	{
		return mat;
	}

	void Box::SetMatrix(DirectX::XMMATRIX m) noexcept
	{
		mat = m;
	}

	void Box::Update(float dt) noexcept
	{
	}

	void Box::SetColor(Graphics& gfx)
	{
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
				{ 1.0f,1.0f,1.0f },
				{ 1.0f,1.0f,1.0f },
				{ 1.0f,1.0f,1.0f },
				{ 0.0f,0.0f,1.0f },
				{ 1.0f,0.0f,1.0f },
				{ 0.0f,1.0f,1.0f },
				{ 0.0f,0.0f,0.0f },
			}
		};
		//ReplaceStaticBindable(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(gfx, cb2));
		AddStaticBind(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(gfx, cb2));
	}
}