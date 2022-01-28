#include "pch.h"
#include "Renderer.h"
#include "Aurora/Core/Application.h"
#include "Aurora/Core/Window.h"
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
			if(e.tex)
				e.tex->Bind();
			count = e.iBuffer->GetCount();
			gfx->DrawIndexed(count);
		}

		m_queue.Queue.clear();
	}

	void Renderer::Submit(Ref<VertexShader> vShader, Ref<PixelShader> pShader, Ref<VertexBuffer> vBuffer, Ref<IndexBuffer> iBuffer)
	{
		m_queue.Submit(vShader, pShader, vBuffer, iBuffer);
	}

	void Renderer::Submit(Ref<VertexShader> vShader, Ref<PixelShader> pShader, Ref<VertexBuffer> vBuffer, Ref<IndexBuffer> iBuffer, Ref<Texture> texture)
	{
		m_queue.Submit(vShader, pShader, vBuffer, iBuffer,texture);
	}

	void RenderQueue::Submit(Ref<VertexShader> vShader, Ref<PixelShader> pShader, Ref<VertexBuffer> vBuffer, Ref<IndexBuffer> iBuffer)
	{
		Binds b(vShader, pShader, vBuffer, iBuffer);
		Queue.emplace_back(b);
	}

	void RenderQueue::Submit(Ref<VertexShader> vShader, Ref<PixelShader> pShader, Ref<VertexBuffer> vBuffer, Ref<IndexBuffer> iBuffer, Ref<Texture> tex)
	{
		Binds b(vShader, pShader, vBuffer, iBuffer);
		b.tex = tex;
		Queue.emplace_back(b);
	}


}