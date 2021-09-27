#pragma once

#include "D3D11ConstantBuffers.h"
#include "Aurora/Drawables/Drawable.h"
#include <DirectXMath.h>


namespace Aurora {

	class D3D11TransformCbuf : public Bindables
	{
	public:
		D3D11TransformCbuf(const Drawable& parent);
		void Bind() noexcept override;

	private:
		static std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> pVcbuf;
		const Drawable& parent;
	};
}