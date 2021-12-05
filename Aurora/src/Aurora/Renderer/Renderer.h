#pragma once

#include "BindableBase.h"

namespace Aurora {

	class Renderer
	{
	public:
		static void Init();
		static void ShutDown();
		static void BeginScene();
		static void EndScene();
		static void Submit(
			std::shared_ptr<VertexShader> vShader, 
			std::shared_ptr<PixelShader> pShader,
			std::shared_ptr<VertexBuffer> vBuffer,
			std::shared_ptr<IndexBuffer> iBuffer
		);
	private:
		static unsigned int count;
	};

	struct RenderQueue
	{
	public:
		struct Binds
		{
			Ref<VertexShader> vShader;
			Ref<PixelShader> pShader;
			Ref<VertexBuffer> vBuffer;
			Ref<IndexBuffer> iBuffer;

			Binds(
				Ref<VertexShader> vShader,
				Ref<PixelShader> pShader,
				Ref<VertexBuffer> vBuffer,
				Ref<IndexBuffer> iBuffer
			)
			{

			}
		};
		std::vector<Binds> Queue;
	};

}