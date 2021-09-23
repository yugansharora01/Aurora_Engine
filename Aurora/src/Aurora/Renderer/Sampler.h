#pragma once

#include "Bindable.h"

namespace Aurora {

	class Sampler : public Bindable
	{
	public:
		Sampler(Graphics& gfx);
		void Bind(Graphics& gfx) noexcept override;
	protected:
		Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
	};
}