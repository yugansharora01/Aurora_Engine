#pragma once

#include "Platform/Windows/Graphics.h"
#include "Platform/Windows/DxgiInfoManager.h"

namespace Aurora {
	class Bindables
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		static Graphics& Getgfx();
		static DxgiInfoManager& GetInfoManager() noexcept (AU_DEBUG);
	};
}