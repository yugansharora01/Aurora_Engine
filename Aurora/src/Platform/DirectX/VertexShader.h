#pragma once

#include "Bindable.h"

namespace Aurora {

	class VertexShader : public Bindable
	{
	public:
		VertexShader(Graphics& gfx, const std::wstring& path);
		void Bind(Graphics& gfx) noexcept override;
		ID3DBlob* GetBytecode() const noexcept;

	private:
		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	};
}