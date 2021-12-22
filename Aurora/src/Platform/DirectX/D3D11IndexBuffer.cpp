#include "pch.h"
#include "D3D11IndexBuffer.h"
#include "Platform/Windows/GraphicsThrowMacros.h"

namespace Aurora {

    D3D11IndexBuffer::D3D11IndexBuffer(const std::vector<unsigned short>& indices)
        :count((UINT)indices.size())
    {
        Indices = indices;
        INFOMAN;

        ibd = {};
        ibd.ByteWidth = count * sizeof(unsigned short);
        ibd.Usage = D3D11_USAGE_DEFAULT;
        ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        ibd.CPUAccessFlags = 0u;
        ibd.MiscFlags = 0u;
        ibd.StructureByteStride = sizeof(unsigned short);

        isd = {};
        isd.pSysMem = indices.data();

        GFX_THROW_INFO(Getgfx()->GetDevice()->CreateBuffer(&ibd, &isd, &pIndexBuffer));
    }

    void D3D11IndexBuffer::Bind()
    {
        Getgfx()->GetContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
    }

    void D3D11IndexBuffer::Unbind()
    {
    }


    UINT D3D11IndexBuffer::GetCount() const noexcept
    {
        return count;
    }
}