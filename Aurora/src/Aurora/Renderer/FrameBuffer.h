#pragma once

#include "Bindables.h"

namespace Aurora {

	class FrameBuffer : public Bindables
	{
	public:
		virtual ~FrameBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual void* GetBufferAsTexture() = 0;
		
		static std::shared_ptr<FrameBuffer> Create(unsigned int width, unsigned int height);
	};

}