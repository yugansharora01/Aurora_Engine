#pragma once

#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class D3D11Sampler : public Bindables
	{
	public:
		D3D11Sampler();
		void Bind() ;
		void Unbind() {}
	protected:
		Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
	};
}