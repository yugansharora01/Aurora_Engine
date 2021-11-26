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
		m_DepthStencil->SetTarget();
		m_DepthStencil->Bind();
	}
	
	void D3D11FrameBuffer::Unbind()
	{
		m_DepthStencil->SetTarget();
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

		int Width = 800;
		int Height = 600;

		/*ID3D11Texture2D* pBackBuffer;
		GFX_THROW_INFO(Getgfx()->GetSwap()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer));
		ID3D11Texture2D* tex = NULL;
		D3D11_TEXTURE2D_DESC td;
		pBackBuffer->GetDesc(&td);
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateTexture2D(&td, NULL, &tex));
		Getgfx()->GetContext()->CopyResource(tex,pBackBuffer);*/
		
		
		

		D3D11_TEXTURE2D_DESC textureDesc;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;

		///////////////////////// Map's Texture
		// Initialize the  texture description.
		ZeroMemory(&textureDesc, sizeof(textureDesc));

		// Setup the texture description.
		// We will have our map be a square
		// We will need to have this texture bound as a render target AND a shader resource
		textureDesc.Width = Width / 2;
		textureDesc.Height = Height / 2;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		// Create the texture
		Getgfx()->GetDevice()->CreateTexture2D(&textureDesc, NULL, &renderTargetTextureMap);

		/////////////////////// Map's Render Target
		// Setup the description of the render target view.
		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		// Create the render target view.
		Getgfx()->GetDevice()->CreateRenderTargetView(renderTargetTextureMap.Get(), &renderTargetViewDesc, &renderTargetViewMap);

		// Set our maps Render Target
		Getgfx()->GetContext()->OMSetRenderTargets(1, &renderTargetViewMap, Getgfx()->GetDepthStencil().Get());


		const float bgColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		// Now clear the render target
		Getgfx()->GetContext()->ClearRenderTargetView(renderTargetViewMap.Get(), bgColor);


		return (void*)renderTargetTextureMap.Get();
	}

	void D3D11FrameBuffer::Clear(float red, float green, float blue)
	{
		const float bgColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		// Now clear the render target
		Getgfx()->GetContext()->ClearRenderTargetView(renderTargetViewMap.Get(), bgColor);
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
	}
}



