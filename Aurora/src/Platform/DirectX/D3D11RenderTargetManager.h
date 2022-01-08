#pragma once

#include "Aurora/Renderer/RenderTargetManager.h"
#include "D3D11DepthStencil.h"
#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	struct RenderTargetBundle
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> resourceview;
		RenderTargetProperties properties;
	};

	class D3D11RenderTargetManager : public RenderTargetManager , public Bindables
	{
	public:
		D3D11RenderTargetManager();
		D3D11RenderTargetManager(unsigned int width,unsigned int height);
		virtual void Bind() override;
		virtual void Unbind() override;//this unbinds the depth stencil only
		virtual void Resize(unsigned int width, unsigned int height) override;
		virtual void* GetTextureAsPointer(std::string str) override;
		virtual void* GetTextureData(std::string str) override;
		virtual void Clear(float red, float green, float blue,float alpha) override;
		virtual void RenderToBackBuf() override;
		virtual void AddRenderTarget(std::string str, RenderTargetProperties property) override;
		virtual unsigned int GetNumberOfTargets() { return (unsigned int)RenderTargetArray.size(); }
		virtual void BindTargets() override;
	private:
		static unsigned int s_Width;
		static unsigned int s_Height;
		std::shared_ptr<DepthStencil> m_DepthStencil;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_BackbufRDV;

		static std::unordered_map<std::string, RenderTargetBundle> RenderTargetMap;
		std::vector< Microsoft::WRL::ComPtr<ID3D11RenderTargetView>> RenderTargetArray;
	};

}