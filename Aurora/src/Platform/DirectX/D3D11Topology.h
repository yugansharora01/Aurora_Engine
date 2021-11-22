#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Aurora/Renderer/Buffer.h"

namespace Aurora {

	class D3D11Topology : public Topology , public Bindables
	{
	public:
		D3D11Topology(TopologyType type);
		void Bind() ;
		void Unbind() {}
	private:
		D3D11_PRIMITIVE_TOPOLOGY type;
	};
}