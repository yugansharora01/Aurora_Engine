#include "pch.h"
#include "D3D11Topology.h"

namespace Aurora {

	static D3D11_PRIMITIVE_TOPOLOGY TopologyTypeToD3D11Topology(TopologyType type)
	{
		switch (type)
		{
		case Aurora::TopologyType::Point_List: return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
			break;
		case Aurora::TopologyType::Line_List: return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
			break;
		case Aurora::TopologyType::Line_Strip: return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
			break;
		case Aurora::TopologyType::Triangle_List: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		case Aurora::TopologyType::Triangle_Strip: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			break;
		default:
			break;
		}
	}

	D3D11Topology::D3D11Topology(TopologyType type)
		:type(TopologyTypeToD3D11Topology(type))
	{
	}

	void D3D11Topology::Bind() 
	{
		Getgfx().GetContext()->IASetPrimitiveTopology(type);
	}
}