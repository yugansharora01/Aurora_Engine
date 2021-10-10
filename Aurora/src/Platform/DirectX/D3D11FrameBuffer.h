#pragma once

#include "Aurora/Renderer/FrameBuffer.h"
#include "D3D11DepthStencil.h"

namespace Aurora {

	class D3D11FrameBuffer : public FrameBuffer
	{
	public:
		D3D11FrameBuffer();
		D3D11FrameBuffer(unsigned int width,unsigned int height);
		virtual void Bind() override;
		virtual void Unbind() override;//this unbinds the depth stencil only
		virtual void Resize(unsigned int width, unsigned int height) override;
		void RefreshBackBuffer();
		static bool IsBound() { return bound; }
	private:
		static bool bound;
		static unsigned int s_Width;
		static unsigned int s_Height;
		std::shared_ptr<DepthStencil> m_DepthStencil;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	};

}