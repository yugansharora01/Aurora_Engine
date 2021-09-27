#pragma once

#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class D3D11Topology : public Bindables
	{
	public:
		D3D11Topology(D3D11_PRIMITIVE_TOPOLOGY type);
		void Bind() noexcept override;

	private:
		D3D11_PRIMITIVE_TOPOLOGY type;
	};
}