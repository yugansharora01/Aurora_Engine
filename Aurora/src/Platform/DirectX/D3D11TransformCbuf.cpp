#include "pch.h"
#include "D3D11TransformCbuf.h"

namespace Aurora {

	D3D11TransformCbuf::D3D11TransformCbuf(const Drawable& parent)
		:parent(parent)
	{
		DirectX::XMMATRIX mat = DirectX::XMMatrixIdentity();
		if (!pVcbuf)
		{
			pVcbuf = std::make_unique<D3D11VertexConstantBuffer>();
		}
	}

	void D3D11TransformCbuf::Bind() 
	{
		pVcbuf->Update(DirectX::XMMatrixTranspose(
			parent.GetTransformXM() * Getgfx().GetProjection()
		));
		pVcbuf->Bind();
	}

	std::unique_ptr<D3D11VertexConstantBuffer> D3D11TransformCbuf::pVcbuf;

}
