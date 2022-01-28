#include "pch.h"
#include "D3D11RenderTargetManager.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "Aurora/Core/Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include "DirectXHelperFunc.h"

namespace Aurora {
	unsigned int D3D11RenderTargetManager::s_Width = 800;
	unsigned int D3D11RenderTargetManager::s_Height = 600;
	std::unordered_map<std::string, RenderTargetBundle> D3D11RenderTargetManager::RenderTargetMap;

	D3D11RenderTargetManager::D3D11RenderTargetManager()
	{
		RenderToBackBuf();
		m_DepthStencil = std::make_shared<DepthStencil>(s_Width, s_Height);
	}
	D3D11RenderTargetManager::D3D11RenderTargetManager(unsigned int width, unsigned int height)
	{
		s_Width = width;
		s_Height = height;
		RenderToBackBuf();
		m_DepthStencil = std::make_shared<DepthStencil>(width, height);
	}
	
	void D3D11RenderTargetManager::Bind()
	{
		Getgfx()->GetContext()->OMSetRenderTargets(1u, m_BackbufRDV.GetAddressOf(), m_DepthStencil->pDSV.Get());
	}
	
	void D3D11RenderTargetManager::Unbind()
	{
		Getgfx()->GetContext()->OMSetRenderTargets(1u, m_BackbufRDV.GetAddressOf(), NULL);
	}

	void D3D11RenderTargetManager::Resize(unsigned int width, unsigned int height)
	{
		s_Width = width;
		s_Height = height;
		m_DepthStencil->Create(width, height);

		auto map = RenderTargetMap;
		RenderTargetMap.clear();
		RenderTargetArray.clear();

		for (auto& renderTarget : map)
		{
			renderTarget.second.properties.Width = width;
			renderTarget.second.properties.Height = height;
			AddRenderTarget(renderTarget.first,renderTarget.second.properties);
		}
	}

	void* D3D11RenderTargetManager::GetTextureAsPointer(std::string str)
	{		
		return (void*)RenderTargetMap[str].resourceview.Get();
	}

	void* D3D11RenderTargetManager::GetTextureData(std::string str)
	{
		INFOMAN;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture;

		D3D11_TEXTURE2D_DESC textureDesc;
		auto properties = RenderTargetMap[str].properties;

		// Initialize the  texture description.
		ZeroMemory(&textureDesc, sizeof(textureDesc));

		textureDesc.Width = properties.Width;
		textureDesc.Height = properties.Height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1u;
		textureDesc.Format = DXGI_FORMAT_R32_FLOAT;// GetPropertiesFormat(properties.Format.IsNormalised, properties.Format.type, properties.Format.NumberOfBits);
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_STAGING;
		textureDesc.BindFlags = 0u;
		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ ;
		textureDesc.MiscFlags = 0;

		// Create the texture
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateTexture2D(&textureDesc, NULL, &Texture));

		Getgfx()->GetContext()->CopyResource(Texture.Get(), RenderTargetMap[str].texture.Get());
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		Getgfx()->GetContext()->Map(Texture.Get(), 0, D3D11_MAP_READ, 0, &mappedResource);

		AU_INFO("Rowpitch = {0}", mappedResource.RowPitch/sizeof(float));

		return mappedResource.pData;
	}


	void D3D11RenderTargetManager::Clear(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f)
	{
		const float bgColor[] = { red, green, blue , alpha };
		// Now clear the render target
		for (auto targetbundle : RenderTargetMap)
		{
			Getgfx()->GetContext()->ClearRenderTargetView(targetbundle.second.target.Get(), bgColor);
		}
		Getgfx()->GetContext()->ClearDepthStencilView(m_DepthStencil->pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
		
	}

	void D3D11RenderTargetManager::RenderToBackBuf()
	{
		INFOMAN;

		//gain access to texture subresource in swap chain (back buffer)
		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
		GFX_THROW_INFO(Getgfx()->GetSwap()->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer));
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_BackbufRDV));

		if(m_DepthStencil == nullptr)
			m_DepthStencil = std::make_shared<DepthStencil>(s_Width, s_Height);

		Bind();
	}

	void D3D11RenderTargetManager::AddRenderTarget(std::string str,RenderTargetProperties properties)
	{
		INFOMAN;

		if (properties.Width == 0 || properties.Height == 0)
		{
			properties.Width = s_Width;
			properties.Height = s_Height;
		}

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTargetTexture;
		RenderTargetBundle bundle;

		D3D11_TEXTURE2D_DESC textureDesc;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;

		unsigned int BindFlags = D3D11_BIND_RENDER_TARGET;
		if (properties.IsDataAccessable)
			BindFlags |= D3D11_BIND_SHADER_RESOURCE;

		// Initialize the  texture description.
		ZeroMemory(&textureDesc, sizeof(textureDesc));

		// Setup the render target texture description
		textureDesc.Width = properties.Width;
		textureDesc.Height = properties.Height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = properties.NumberOfTargets;
		textureDesc.Format = GetPropertiesFormat(properties.Format.IsNormalised, properties.Format.type, properties.Format.NumberOfBits);
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = properties.IsCPUAccessable ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = BindFlags;
		textureDesc.CPUAccessFlags = properties.IsCPUAccessable ? D3D11_CPU_ACCESS_READ : D3D11_CPU_ACCESS_WRITE;
		textureDesc.MiscFlags = 0;

		// Create the texture
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateTexture2D(&textureDesc, NULL, &renderTargetTexture));

		// Setup the description of the render target view.
		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		// Create the render target view.
		GFX_THROW_INFO(Getgfx()->GetDevice()->CreateRenderTargetView(renderTargetTexture.Get(), &renderTargetViewDesc, &renderTarget));

		bundle.texture = renderTargetTexture;
		bundle.target = renderTarget;
		bundle.properties = properties;

		if (properties.IsDataAccessable)
		{
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;

			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
			ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));

			// Setup the description of the shader resource view.
			shaderResourceViewDesc.Format = textureDesc.Format;
			shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
			shaderResourceViewDesc.Texture2D.MipLevels = 1;

			// Create the shader resource view.
			Getgfx()->GetDevice()->CreateShaderResourceView(renderTargetTexture.Get(), &shaderResourceViewDesc, shaderResourceView.GetAddressOf());
			bundle.resourceview = shaderResourceView;
		}
		RenderTargetMap.emplace(str, bundle);
		RenderTargetArray.push_back(renderTarget);
	}

	void D3D11RenderTargetManager::BindTargets()
	{
		Getgfx()->GetContext()->OMSetRenderTargets((unsigned int)RenderTargetArray.size(), RenderTargetArray[0].GetAddressOf(), m_DepthStencil->pDSV.Get());
	}

}