#pragma once


namespace Aurora {

	class D3D11Graphics;
	class FrameBuffer;

	class Graphics
	{
	public: 
		static Ref<FrameBuffer> fbuf;

	public:
		virtual void EndFrame() = 0;
		virtual void ClearBuffer(float red, float green, float blue) noexcept = 0;
		virtual void DrawIndexed(unsigned int count) AU_RELEASENOEXCEPT = 0;
		virtual void SetViewPort(unsigned int width, unsigned int height) = 0;
		virtual void RenderToTex() = 0;

		static Ref<Graphics> Create(void* arg);


	};


}