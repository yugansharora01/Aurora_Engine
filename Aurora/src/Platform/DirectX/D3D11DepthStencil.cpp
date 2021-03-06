#include "pch.h"
#include "D3D11DepthStencil.h"
#include "Platform/Windows/GraphicsThrowMacros.h"

namespace Aurora {
	DepthStencil::DepthStencil(unsigned int width, unsigned int height)
		:m_width(width),m_height(height)
	{
		Create(width, height);
	}

	void DepthStencil::Create(unsigned int width, unsigned int height)
	{
		m_width = width;
		m_height = height;
		INFOMAN;

		//create depth stensil state
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateDepthStencilState(&dsDesc, &pDSState));

		//bind depth state
		Getgfx()->GetContext()->OMSetDepthStencilState(pDSState.Get(), 1u);

		D3D11_TEXTURE2D_DESC descDepth = {};
		descDepth.Width = m_width;
		descDepth.Height = m_height;
		descDepth.MipLevels = 1u;
		descDepth.ArraySize = 1u;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1u;
		descDepth.SampleDesc.Quality = 0u;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));

		//create view of depth stencil texture
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.Format = DXGI_FORMAT_D32_FLOAT;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0u;

		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateDepthStencilView(
			pDepthStencil.Get(), &descDSV, &pDSV
		));
	}

}