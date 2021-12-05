#include "pch.h"
#include "Renderer.h"
#include "Aurora/Application.h"
#include "Aurora/Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Aurora {

	unsigned int Renderer::count = 0u;
	RenderQueue Renderer::m_queue;

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
		auto gfx = Application::Get().GetWindow().Gfx();

		for (auto& e : m_queue.Queue)
		{
			e.vBuffer->Bind();
			e.vShader->Bind();
			e.pShader->Bind();
			e.iBuffer->Bind();
			count = e.iBuffer->GetCount();
			gfx->DrawIndexed(count);
		}

		m_queue.Queue.clear();
		//gfx->DrawIndexed(count);
	}

	void Renderer::Submit(std::shared_ptr<VertexShader> vShader, std::shared_ptr<PixelShader> pShader, std::shared_ptr<VertexBuffer> vBuffer, std::shared_ptr<IndexBuffer> iBuffer)
	{
		m_queue.Submit(vShader, pShader, vBuffer, iBuffer);
		/*vBuffer->Bind(); 
		vShader->Bind();
		pShader->Bind();
		iBuffer->Bind();
		count = iBuffer->GetCount();*/
	}

	void RenderQueue::Submit(Ref<VertexShader> vShader, Ref<PixelShader> pShader, Ref<VertexBuffer> vBuffer, Ref<IndexBuffer> iBuffer)
	{
		Binds b(vShader, pShader, vBuffer, iBuffer);
		Queue.emplace_back(b);
	}

}