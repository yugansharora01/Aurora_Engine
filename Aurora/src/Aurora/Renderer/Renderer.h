#pragma once

#include "BindableBase.h"

namespace Aurora {

	class RenderQueue
	{
		struct Binds
		{
		public:
			Ref<VertexShader> vShader;
			Ref<PixelShader> pShader;
			Ref<VertexBuffer> vBuffer;
			Ref<IndexBuffer> iBuffer;

			Binds(
				Ref<VertexShader> VertexShader,
				Ref<PixelShader> PixelShader,
				Ref<VertexBuffer> VertexBuffer,
				Ref<IndexBuffer> IndexBuffer
			)
				:vShader(VertexShader), pShader(PixelShader), vBuffer(VertexBuffer), iBuffer(IndexBuffer)
			{

			}
		};
	public:

		std::vector<Binds> Queue;

	public:
		RenderQueue() = default;
		void Submit(
			Ref<VertexShader> vShader,
			Ref<PixelShader> pShader,
			Ref<VertexBuffer> vBuffer,
			Ref<IndexBuffer> iBuffer
		);

		void bind() {}
	};
	

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
		static RenderQueue m_queue;
	};

	

}