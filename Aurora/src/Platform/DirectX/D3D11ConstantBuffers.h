#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Platform/Windows/GraphicsThrowMacros.h"

namespace Aurora {

	
	class D3D11ConstantBuffer : public Bindables
	{
	public:
		template<typename C>
		void Update(const C& consts)
		{
			INFOMAN;
			D3D11_MAPPED_SUBRESOURCE msr;
			GFX_THROW_INFO(Getgfx().GetContext()->Map(
				pConstantBuffer.Get(), 0u,
				D3D11_MAP_WRITE_DISCARD, 0u,
				&msr
			));
			memcpy(msr.pData, &consts, sizeof(consts));
			Getgfx().GetContext()->Unmap(pConstantBuffer.Get(), 0u);
		}

		D3D11ConstantBuffer()
		{
			
		}

		template<typename T>
		void Create()
		{
			INFOMAN;

			D3D11_BUFFER_DESC cbd;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.MiscFlags = 0u;
			cbd.ByteWidth = sizeof(T);
			cbd.StructureByteStride = 0u;

			GFX_THROW_INFO(Getgfx().GetDevice()->CreateBuffer(&cbd, nullptr, &pConstantBuffer));
		}

		template<typename T>
		void Create(const T& consts)
		{
			INFOMAN;
			D3D11_BUFFER_DESC cbd;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.MiscFlags = 0u;
			cbd.ByteWidth = sizeof(consts);
			cbd.StructureByteStride = 0u;

			D3D11_SUBRESOURCE_DATA csd = {};
			csd.pSysMem = &consts;
			GFX_THROW_INFO(Getgfx().GetDevice()->CreateBuffer(&cbd, &csd, &pConstantBuffer));
		}
		virtual void Bind() noexcept = 0;
		virtual void Unbind() noexcept = 0;
	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	};


	class D3D11VertexConstantBuffer : public D3D11ConstantBuffer
	{
		using Bindables::Getgfx;
		using D3D11ConstantBuffer::Bind;
		using D3D11ConstantBuffer::Unbind;
		using D3D11ConstantBuffer::pConstantBuffer;
		using D3D11ConstantBuffer::D3D11ConstantBuffer;
	public:
		virtual void Bind() noexcept override
		{
			Getgfx().GetContext()->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
		}
		virtual void Unbind() noexcept override {}
	};


	class D3D11PixelConstantBuffer : public D3D11ConstantBuffer
	{
	public:
		using Bindables::Getgfx;
		using D3D11ConstantBuffer::Bind;
		using D3D11ConstantBuffer::Unbind;
		using D3D11ConstantBuffer::pConstantBuffer;
		using D3D11ConstantBuffer::D3D11ConstantBuffer;

		virtual void Bind() noexcept override
		{
			Getgfx().GetContext()->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
		}
		virtual void Unbind() noexcept override {}
	};

















	/*class D3D11VertexConstantBuffer : public VertexConstantBuffer
	{

	public:
		D3D11VertexConstantBuffer()
		{
			INFOMAN;

			D3D11_BUFFER_DESC cbd;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.MiscFlags = 0u;
			cbd.ByteWidth = sizeof(DirectX::XMMATRIX);
			cbd.StructureByteStride = 0u;

			GFX_THROW_INFO(Getgfx().GetDevice()->CreateBuffer(&cbd, nullptr, &pConstantBuffer));
		}

		D3D11VertexConstantBuffer(const DirectX::XMMATRIX& consts)
		{
			INFOMAN;
			D3D11_BUFFER_DESC cbd;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.MiscFlags = 0u;
			cbd.ByteWidth = sizeof(consts);
			cbd.StructureByteStride = 0u;

			D3D11_SUBRESOURCE_DATA csd = {};
			csd.pSysMem = &consts;
			GFX_THROW_INFO(Getgfx().GetDevice()->CreateBuffer(&cbd, &csd, &pConstantBuffer));
		}

		void Update(const DirectX::XMMATRIX& consts) override
		{
			INFOMAN;
			D3D11_MAPPED_SUBRESOURCE msr;
			GFX_THROW_INFO(Getgfx().GetContext()->Map(
				pConstantBuffer.Get(), 0u,
				D3D11_MAP_WRITE_DISCARD, 0u,
				&msr
			));
			memcpy(msr.pData, &consts, sizeof(consts));
			Getgfx().GetContext()->Unmap(pConstantBuffer.Get(), 0u);
		}

		void Bind() override
		{
			Getgfx().GetContext()->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
		}

		void Unbind() override
		{
		}
	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	};

	class D3D11PixelConstantBuffer : public PixelConstantBuffer
	{
	public:
		D3D11PixelConstantBuffer()
		{
			INFOMAN;
				
			D3D11_BUFFER_DESC cbd;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.MiscFlags = 0u;
			cbd.ByteWidth = sizeof(std::array<DirectX::XMFLOAT4, 8>);
			cbd.StructureByteStride = 0u;

			GFX_THROW_INFO(Getgfx().GetDevice()->CreateBuffer(&cbd, nullptr, &pConstantBuffer));
		}

		D3D11PixelConstantBuffer(const std::array<DirectX::XMFLOAT4, 8>& consts)
		{
			INFOMAN;

			D3D11_BUFFER_DESC cbd;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.MiscFlags = 0u;
			cbd.ByteWidth = sizeof(consts);
			cbd.StructureByteStride = 0u;

			D3D11_SUBRESOURCE_DATA csd = {};
			csd.pSysMem = &consts;
			GFX_THROW_INFO(Getgfx().GetDevice()->CreateBuffer(&cbd, &csd, &pConstantBuffer));
		}

		void Update(const std::array<DirectX::XMFLOAT4, 8>& consts) override
		{
			INFOMAN;
			D3D11_MAPPED_SUBRESOURCE msr;
			GFX_THROW_INFO(Getgfx().GetContext()->Map(
				pConstantBuffer.Get(), 0u,
				D3D11_MAP_WRITE_DISCARD, 0u,
				&msr
			));
			memcpy(msr.pData, &consts, sizeof(consts));
			Getgfx().GetContext()->Unmap(pConstantBuffer.Get(), 0u);
		}

		void Bind() override
		{
			Getgfx().GetContext()->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
		}

		void Unbind() override
		{
		}
	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	};*/
}