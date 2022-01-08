#include "pch.h"
#include "D3D11Buffers.h"
#include "Aurora/Renderer/RenderTargetManager.h"

namespace Aurora
{
	void D3D11PixelStructuredBuffer::Create(unsigned int Elements, unsigned int EleSize, void* data)
	{
		m_Elements = Elements;
		m_EleSize = EleSize;

		cbd = {};
		cbd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		cbd.StructureByteStride = EleSize;
		cbd.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		cbd.Usage = D3D11_USAGE_DEFAULT;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


		CreateNew(Elements * EleSize, data);

		D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		uavDesc.Buffer.FirstElement = 0;
		uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_APPEND;
		uavDesc.Buffer.NumElements = Elements;

		Getgfx()->GetDevice()->CreateUnorderedAccessView(Buffers[0].Get(), &uavDesc, UAVview.GetAddressOf());
	}

	void* D3D11PixelStructuredBuffer::GetData()
	{

		cbd = {};

		cbd.MiscFlags = 0u;
		cbd.StructureByteStride = 0u;
		cbd.BindFlags = 0;
		cbd.Usage = D3D11_USAGE_STAGING;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;

		CreateNew(m_Elements * m_EleSize);

		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer = Buffers.back();
		Buffers.pop_back();

		Getgfx()->GetContext()->CopyResource(buffer.Get(),Buffers[0].Get());
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		Getgfx()->GetContext()->Map(buffer.Get(), 0, D3D11_MAP_READ, 0, &mappedResource);

		return mappedResource.pData;

	}

	void D3D11PixelStructuredBuffer::Bind() noexcept
	{
		auto startslot = (UINT)Getgfx()->TargetManager->GetNumberOfTargets() + 1;
		unsigned int l = 1u;
		Getgfx()->GetContext()->OMSetRenderTargetsAndUnorderedAccessViews(
			D3D11_KEEP_RENDER_TARGETS_AND_DEPTH_STENCIL,
			NULL,NULL,
			startslot,
			1u,
			UAVview.GetAddressOf(),
			&l
		);
	}
}