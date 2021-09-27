#include "pch.h"
#include "D3D11Topology.h"

namespace Aurora {

	D3D11Topology::D3D11Topology(D3D11_PRIMITIVE_TOPOLOGY type)
		:type(type)
	{
	}

	void D3D11Topology::Bind() noexcept
	{
		Getgfx().GetContext()->IASetPrimitiveTopology(type);
	}
}