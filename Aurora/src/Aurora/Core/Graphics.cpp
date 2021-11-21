#include "pch.h"
#include "Graphics.h"
#include "Platform/DirectX/D3D11Graphics.h"

namespace Aurora
{
	static Ref<Graphics> Create()
	{
		return CreateRef<D3D11Graphics>();
	}
}