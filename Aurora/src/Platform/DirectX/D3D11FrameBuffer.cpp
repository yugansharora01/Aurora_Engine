#include "pch.h"
#include "D3D11FrameBuffer.h"
#include "Platform/Windows/GraphicsThrowMacros.h"

namespace Aurora {

	bool D3D11FrameBuffer::bound = false;
	unsigned int D3D11FrameBuffer::s_Width = 800;
	unsigned int D3D11FrameBuffer::s_Height = 600;

	D3D11FrameBuffer::D3D11FrameBuffer()
	{
		RefreshBackBuffer();
		m_DepthStencil = std::make_shared<DepthStencil>(s_Width, s_Height);
	}
	D3D11FrameBuffer::D3D11FrameBuffer(unsigned int width, unsigned int height)
	{
		s_Width = width;
		s_Height = height;
		RefreshBackBuffer();
		m_DepthStencil = std::make_shared<DepthStencil>(width, height);
	}
	
	void D3D11FrameBuffer::Bind()
	{
		RefreshBackBuffer();
		m_DepthStencil->SetTarget(pTarget);
		m_DepthStencil->Bind();
	}
	
	void D3D11FrameBuffer::Unbind()
	{
		m_DepthStencil->SetTarget(pTarget);
		m_DepthStencil->Unbind();
	}
	void D3D11FrameBuffer::Resize(unsigned int width, unsigned int height)
	{
		s_Width = width;
		s_Height = height;
		RefreshBackBuffer();
		m_DepthStencil->Create(width, height);
	}

	void* D3D11FrameBuffer::GetBufferAsTexture()
	{
		INFOMAN;

		int Width = s_Width;
		int Height = s_Height;
			

		D3D11_TEXTURE2D_DESC textureDesc;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;

		///////////////////////// Map's Texture
		// Initialize the  texture description.
		ZeroMemory(&textureDesc, sizeof(textureDesc));

		// Setup the render target texture description
		textureDesc.Width = Width;
		textureDesc.Height = Height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		// Create the texture
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateTexture2D(&textureDesc, NULL, &m_renderTargetTexture));

		/////////////////////// Map's Render Target
		// Setup the description of the render target view.
		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		// Create the render target view.
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateRenderTargetView(m_renderTargetTexture.Get(), &renderTargetViewDesc, &m_renderTargetView));

		// Set our maps Render Target
		Getgfx()->GetContext()->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_DepthStencil->pDSV.Get());


		//const float bgColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		// Now clear the render target
		//Getgfx()->GetContext()->ClearRenderTargetView(m_renderTargetView.Get(), bgColor);


		return (void*)m_renderTargetTexture.Get();
	}

	void D3D11FrameBuffer::Clear(float red, float green, float blue , float alpha = 0.0f)
	{
		const float bgColor[] = { red, green, blue , alpha };
		// Now clear the render target
		Getgfx()->GetContext()->ClearRenderTargetView(m_renderTargetView.Get(), bgColor);
	}

	void D3D11FrameBuffer::RefreshBackBuffer()
	{
		INFOMAN;

		//gain access to texture subresource in swap chain (back buffer)

		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
		GFX_THROW_INFO(Getgfx()->GetSwap()->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer));
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget));

		//create depth stensil state
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateDepthStencilState(&dsDesc, &pDSState));

		//bind depth state
		Getgfx()->GetContext()->OMSetDepthStencilState(pDSState.Get(), 1u);
	}
}



