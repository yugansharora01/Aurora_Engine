#include "pch.h"
#include "Renderer.h"
#include "Aurora/Application.h"
#include "Aurora/Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Aurora {

	unsigned int Renderer::count = 0u;

	void Renderer::Init()
	{
		//TO DO it will take camera and other scene parameters
	}

	void Renderer::ShutDown()
	{
		//TO DO Free everything if anything is required to be freed
	}

	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{
		auto gfx = (D3D11Graphics*)Application::Get().GetWindow().Gfx()->NativeGraphicsObject;
		gfx->DrawIndexed(count);
	}

	void Renderer::Submit(std::shared_ptr<VertexShader> vShader, std::shared_ptr<PixelShader> pShader, std::shared_ptr<VertexBuffer> vBuffer, std::shared_ptr<IndexBuffer> iBuffer)
	{
		vBuffer->Bind(); 
		vShader->Bind();
		pShader->Bind();
		iBuffer->Bind();
		count = iBuffer->GetCount();
	}

}