#include "pch.h"
#include "FrameBuffer.h"
#include "Platform/DirectX/D3D11FrameBuffer.h"

namespace Aurora {
	std::shared_ptr<FrameBuffer> FrameBuffer::Create(unsigned int width, unsigned int height)
	{
		return std::make_shared<D3D11FrameBuffer>(width,height);
	}
}