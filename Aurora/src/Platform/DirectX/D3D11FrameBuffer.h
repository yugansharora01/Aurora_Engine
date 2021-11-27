#pragma once

#include "Aurora/Renderer/FrameBuffer.h"
#include "D3D11DepthStencil.h"
#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class D3D11FrameBuffer : public FrameBuffer , public Bindables
	{
	public:
		D3D11FrameBuffer();
		D3D11FrameBuffer(unsigned int width,unsigned int height);
		virtual void Bind() override;
		virtual void Unbind() override;//this unbinds the depth stencil only
		virtual void Resize(unsigned int width, unsigned int height) override;
		virtual void* GetBufferAsTexture() override;
		void RefreshBackBuffer();
		static bool IsBound() { return bound; }
		void Clear(float red, float green, float blue,float alpha);
	private:
		static bool bound;
		static unsigned int s_Width;
		static unsigned int s_Height;
		std::shared_ptr<DepthStencil> m_DepthStencil;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_renderTargetTexture;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;
	};

}