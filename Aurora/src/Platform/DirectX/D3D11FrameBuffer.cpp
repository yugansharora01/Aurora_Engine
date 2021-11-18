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

		ID3D11Texture2D* pBackBuffer;
		GFX_THROW_INFO(Getgfx().GetSwap()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer));
		ID3D11Texture2D* tex = NULL;
		D3D11_TEXTURE2D_DESC td;
		pBackBuffer->GetDesc(&td);
		GFX_THROW_INFO(Getgfx().GetDevice()->CreateTexture2D(&td, NULL, &tex));
		Getgfx().GetContext()->CopyResource(tex,pBackBuffer);
		
		
		return (void*)tex;
	}

	void D3D11FrameBuffer::RefreshBackBuffer()
	{
		INFOMAN;

		//gain access to texture subresource in swap chain (back buffer)

		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
		GFX_THROW_INFO(Getgfx().GetSwap()->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer));
		GFX_THROW_INFO(Getgfx().GetDevice()->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget));

		//create depth stensil state
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;
		GFX_THROW_INFO(Getgfx().GetDevice()->CreateDepthStencilState(&dsDesc, &pDSState));
	}
}



