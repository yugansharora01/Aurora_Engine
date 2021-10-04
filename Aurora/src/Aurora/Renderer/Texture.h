#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Platform/DirectX/D3D11Surface.h"

namespace Aurora {

	class Texture : public Bindables
	{
	public:
		virtual ~Texture() = default;

		static std::shared_ptr<Texture> Create(const Surface& s);
	};
}