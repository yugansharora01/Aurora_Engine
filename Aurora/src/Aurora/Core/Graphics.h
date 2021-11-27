#pragma once
#include <glm/glm.hpp>


namespace Aurora {

	class D3D11Graphics;
	class FrameBuffer;

	class Graphics
	{
	public: 
		static void* NativeGraphicsObject;
		static Ref<FrameBuffer> fbuf;

	public:
		virtual void EndFrame() = 0;
		virtual void ClearBuffer(float red, float green, float blue) noexcept = 0;
		virtual void DrawIndexed(unsigned int count) AU_RELEASENOEXCEPT = 0;
		virtual void SetProjection(glm::mat4 proj) noexcept = 0;
		virtual void SetViewPort(unsigned int width, unsigned int height) = 0;
		virtual void RenderToTex() = 0;

		static Graphics* Create(void* arg);


#ifdef AU_PLATFORM_WINDOWS
		static Ref<D3D11Graphics> GraphicsObject;
#endif // AU_PLATFORM_WINDOWS

	};


}