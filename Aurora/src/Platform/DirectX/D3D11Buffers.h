#pragma once

#include "Aurora/Renderer/Bindables.h"
#include "Platform/Windows/GraphicsThrowMacros.h"

namespace Aurora {
	
	class D3D11Buffer : public Bindables
	{
	public:
		bool HaveData;
	public:
		D3D11Buffer()
		{
			
		}

		virtual ~D3D11Buffer(){};

		virtual void Bind() noexcept = 0;
		virtual void Unbind() noexcept = 0;
		unsigned int GetNumberOfBuffers() { return (unsigned int)Buffers.size(); }
	protected:
		template<typename C>
		void Update(const C& consts)
		{
			INFOMAN;
			D3D11_MAPPED_SUBRESOURCE msr;
			GFX_THROW_INFO(Getgfx()->GetContext()->Map(
				Buffers[GetNumberOfBuffers()].Get(), 0u,
				D3D11_MAP_WRITE_DISCARD, 0u,
				&msr
			));
			memcpy(msr.pData, &consts, sizeof(consts));
			Getgfx()->GetContext()->Unmap(Buffers[GetNumberOfBuffers()].Get(), 0u);
		}

		
		void CreateNew(unsigned int size, void* data = nullptr ,int slot = -1)
		{
			INFOMAN;
			HaveData = true;
			Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

			auto l = size % 16;
			if (l != 0)
			{
				size = 16 * (size / 16 + 1);
			}
			cbd.ByteWidth = size;
			
			if (data == nullptr)
			{
				GFX_THROW_INFO(Getgfx()->GetDevice()->CreateBuffer(&cbd, NULL, &buffer));
			}
			else {
				csd = {};
				csd.pSysMem = data;

				GFX_THROW_INFO(Getgfx()->GetDevice()->CreateBuffer(&cbd, &csd, &buffer));
			}
			

			if (slot <= GetNumberOfBuffers() && slot != -1)
			{
				std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>>::iterator it = Buffers.begin() + slot;
				Buffers.insert(it, buffer);
			}
			else
			{
				Buffers.push_back(buffer);
			}
			
		}

	protected:
		std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> Buffers;
		D3D11_BUFFER_DESC cbd;
		D3D11_SUBRESOURCE_DATA csd;

	};


	class D3D11VertexConstantBuffer : public D3D11Buffer
	{
		using Bindables::Getgfx;
		using D3D11Buffer::Bind;
		using D3D11Buffer::Unbind;
		using D3D11Buffer::Buffers;
		using D3D11Buffer::D3D11Buffer;
	public:
		void Create(unsigned int size, void* data,int slot = -1)
		{
			cbd = {};
			cbd.MiscFlags = 0u;
			cbd.StructureByteStride = 0u;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE ;

			CreateNew(size, data, slot);
		}

		virtual void Bind() noexcept override
		{
			Getgfx()->GetContext()->VSSetConstantBuffers(0u, (UINT)Buffers.size(), Buffers[0].GetAddressOf());
		}
		virtual void Unbind() noexcept override {}
	};


	class D3D11PixelConstantBuffer : public D3D11Buffer
	{
	public:
		using Bindables::Getgfx;
		using D3D11Buffer::Bind;
		using D3D11Buffer::Unbind;
		using D3D11Buffer::Buffers;
		using D3D11Buffer::D3D11Buffer;
	public:
		void Create(unsigned int size, void* data, int slot = -1)
		{
			cbd = {};
			cbd.MiscFlags = 0u;
			cbd.StructureByteStride = 0u;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			CreateNew(size, data,slot);
		}

		virtual void Bind() noexcept override
		{
			Getgfx()->GetContext()->PSSetConstantBuffers(0u, (UINT)Buffers.size(), Buffers[0].GetAddressOf());
		}
		virtual void Unbind() noexcept override {}
	};
	
	class D3D11PixelStructuredBuffer : public D3D11Buffer
	{
	public:
		using Bindables::Getgfx;
		using D3D11Buffer::Bind;
		using D3D11Buffer::Unbind;
		using D3D11Buffer::Buffers;
		using D3D11Buffer::D3D11Buffer;
	public:
		void Create(unsigned int Elements, unsigned int EleSize, void* data);

		void* GetData();

		virtual void Bind() noexcept override;
		virtual void Unbind() noexcept override {}
	private:
		unsigned int m_EleSize;
		unsigned int m_Elements;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> UAVview;
	};

}