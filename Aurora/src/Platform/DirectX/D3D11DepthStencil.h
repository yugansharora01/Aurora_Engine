#pragma once

#include "Aurora/Renderer/Bindables.h"
#include <d3d11.h>
#include <wrl.h>

namespace Aurora {

	class DepthStencil :public Bindables
	{
	public:
		DepthStencil(unsigned int width, unsigned int height);
		~DepthStencil() = default;
		void Create(unsigned int width,unsigned int height);
		virtual void Bind() override;
		virtual void Unbind() override;
		void SetTarget();

	private:
		Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
		int m_width;
		int m_height;
	};

}