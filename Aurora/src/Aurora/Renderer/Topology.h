#pragma once

#include "Bindable.h"

namespace Aurora {

	class Topology : public Bindable
	{
	public:
		Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type);
		void Bind(Graphics& gfx) noexcept override;

	private:
		D3D11_PRIMITIVE_TOPOLOGY type;
	};
}