#include "pch.h"
#include "D3D11Sampler.h"
#include "Platform/Windows/GraphicsThrowMacros.h"

namespace Aurora {

	D3D11Sampler::D3D11Sampler()
	{
		INFOMAN;

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		GFX_THROW_INFO(Getgfx().GetDevice()->CreateSamplerState(&samplerDesc, &pSampler));
	}

	void D3D11Sampler::Bind() 
	{
		Getgfx().GetContext()->PSSetSamplers(0, 1, pSampler.GetAddressOf());
	}
}