#pragma once

#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class PixelShader : public Bindables
	{
	public:
		virtual ~PixelShader() = default;

		static std::shared_ptr<PixelShader> Create(const std::wstring& path);

	};

	class VertexShader : public Bindables
	{
	public:
		virtual ~VertexShader() = default;

		virtual ID3DBlob* GetBytecode() const noexcept = 0;

		static std::shared_ptr<VertexShader> Create(const std::wstring& path);
	};

}