#pragma once

#include "Platform/DirectX/D3D11Surface.h"

namespace Aurora {

	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		static std::shared_ptr<Texture> Create(const std::string path);
	public:
		bool IsEmpty = true;
	};
}