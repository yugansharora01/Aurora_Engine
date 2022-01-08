#pragma once


namespace Aurora {

	class D3D11Graphics;
	class RenderTargetManager;

	class Graphics
	{
	public: 
		static Ref<RenderTargetManager> TargetManager;

	public:
		virtual void EndFrame() = 0;
		virtual void ClearBuffer(float red, float green, float blue) noexcept = 0;
		virtual void DrawIndexed(unsigned int count) AU_RELEASENOEXCEPT = 0;
		virtual void SetViewPort(unsigned int width, unsigned int height) = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
				
		static Ref<Graphics> Create(void* arg,unsigned int width = 800u,unsigned int height = 600u);


	};


}