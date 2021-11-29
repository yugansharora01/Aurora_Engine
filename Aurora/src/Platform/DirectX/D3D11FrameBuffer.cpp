#include "pch.h"
#include "D3D11FrameBuffer.h"
#include "Platform/Windows/GraphicsThrowMacros.h"

namespace Aurora {
	bool IsTargetSet = false;
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
		m_DepthStencil->SetTarget(m_renderTargetView);
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
		m_DepthStencil->Create(width, height);
	}

	void* D3D11FrameBuffer::GetBufferAsTexture()
	{	
		
		if (!IsTargetSet)
		{
			SetRenderTarget();
		}

		
		return (void*)m_shaderResourceView.Get();
	}

	void D3D11FrameBuffer::SetRenderTarget()
	{
		INFOMAN;

		int Width = s_Width;
		int Height = s_Height;


		D3D11_TEXTURE2D_DESC textureDesc;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;

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
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		// Create the texture
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateTexture2D(&textureDesc, NULL, &m_renderTargetTexture));

		// Setup the description of the render target view.
		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		// Create the render target view.
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateRenderTargetView(m_renderTargetTexture.Get(), &renderTargetViewDesc, &m_renderTargetView));

		// Set the Render Target
		Getgfx()->GetContext()->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_DepthStencil->pDSV.Get());


		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
		ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));

		// Setup the description of the shader resource view.
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;

		// Create the shader resource view.
		Getgfx()->GetDevice()->CreateShaderResourceView(m_renderTargetTexture.Get(), &shaderResourceViewDesc, m_shaderResourceView.GetAddressOf());

		Graphics::GraphicsObject->pTarget = m_renderTargetView;
		Graphics::GraphicsObject->pDSV = m_DepthStencil->pDSV;

		IsTargetSet = true;
	}

	void D3D11FrameBuffer::Clear(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f)
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