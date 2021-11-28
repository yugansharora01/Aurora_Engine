#pragma once


namespace Aurora {

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual void* GetBufferAsTexture() = 0;
		virtual void Clear(float red, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f) = 0;
		
		static std::shared_ptr<FrameBuffer> Create(unsigned int width, unsigned int height);
	};

}