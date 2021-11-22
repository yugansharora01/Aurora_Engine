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
	public:
		static unsigned int count;
	};

}