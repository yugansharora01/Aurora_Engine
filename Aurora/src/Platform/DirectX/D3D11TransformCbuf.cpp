#include "pch.h"
#include "D3D11TransformCbuf.h"

namespace Aurora {

	D3D11TransformCbuf::D3D11TransformCbuf(const Drawable& parent)
		:parent(parent)
	{
		if (!pVcbuf)
		{
			pVcbuf = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>();
		}
	}

	void D3D11TransformCbuf::Bind() noexcept
	{
		pVcbuf->Update(DirectX::XMMatrixTranspose(
			parent.GetTransformXM() * Getgfx().GetProjection()
		));
		pVcbuf->Bind();
	}

	std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> D3D11TransformCbuf::pVcbuf;

}
