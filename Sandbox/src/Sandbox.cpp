#include <Aurora.h>
#include <Aurora/Drawables/Geometry/Cube.h>
#include <Aurora/Renderer/BindableBase.h>
#include "Aurora/Application.h"
#include "Aurora/Window.h"
#include "Platform/Windows/WindowsWindow.h"
#include <array>
#include "imgui.h"


class ExampleLayer : public Aurora::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
		
		DirectX::XMFLOAT3 pos;
		
		const auto model = Cube::Make<DirectX::XMFLOAT3>();

		vBuf = Aurora::VertexBuffer::Create(model.vertices);
		vBuf->Bind();

		vShader = Aurora::VertexShader::Create(L"../bin/Debug-windows-x86_64/Aurora/ColorIndexVS.cso");
		vShader->Bind();

		auto pvsbc = vShader->GetBytecode();

		

		pShader = Aurora::PixelShader::Create(L"../bin/Debug-windows-x86_64/Aurora/ColorIndexPS.cso");
		pShader->Bind();

		iBuf = Aurora::IndexBuffer::Create(model.indices);
		iBuf->Bind();

		std::array<DirectX::XMFLOAT3,8> face_colors =
		{
			{
				{ 1.0f,1.0f,1.0f },
				{ 1.0f,0.0f,0.0f },
				{ 0.0f,1.0f,0.0f },
				{ 1.0f,1.0f,0.0f },
				{ 0.0f,0.0f,1.0f },
				{ 1.0f,0.0f,1.0f },
				{ 0.0f,1.0f,1.0f },
				{ 0.0f,0.0f,0.0f },
			}
		};
		pConst = Aurora::PixelConstantBuffer::Create(face_colors);
		pConst->Bind();

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0}
		};
		iLayout = Aurora::InputLayout::Create(ied, pvsbc);
		iLayout->Bind();

		topology = Aurora::Topology::Create(Aurora::TopologyType::Triangle_List);
		topology->Bind();

		auto wnd = (Aurora::Win32_Window*)Aurora::Application::Get().GetWindow().GetNativeWindow();
		auto& gfx = wnd->Gfx();

		vConst = Aurora::VertexConstantBuffer::Create(DirectX::XMMatrixTranspose(
			 gfx.GetProjection()));
		vConst->Bind();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("box");

		ImGui::SliderFloat("x", &x, -100.0f, 100.0f);
		ImGui::SliderFloat("y", &y, -100.0f, 100.0f);
		ImGui::SliderFloat("z", &z, -100.0f, 100.0f);
		
		ImGui::SliderFloat("x1", &x1, 0.0f, 2.0f);
		ImGui::SliderFloat("y1", &y1, 0.0f, 2.0f);
		ImGui::SliderFloat("z1", &z1, 0.0f, 2.0f);

		ImGui::End();
	}
	
	void OnUpdate() override
	{
		auto wnd = (Aurora::Win32_Window*)Aurora::Application::Get().GetWindow().GetNativeWindow();
		auto& gfx = wnd->Gfx();
		vConst = Aurora::VertexConstantBuffer::Create(DirectX::XMMatrixTranspose(
			GetMatrix() * gfx.GetProjection()));

		vBuf->Bind();
		vShader->Bind();
		pShader->Bind();
		iBuf->Bind();
		pConst->Bind();
		iLayout->Bind();
		topology->Bind();
		vConst->Bind();




		gfx.DrawIndexed(iBuf->GetCount());
	}

	DirectX::XMMATRIX GetMatrix()
	{
		return DirectX::XMMatrixRotationRollPitchYaw(x1, y1, z1) * 
				DirectX::XMMatrixTranslation(x, y, z);
	}

	void OnEvent(Aurora::Event& event) override
	{
	}

private:
	std::shared_ptr<Aurora::VertexBuffer> vBuf;
	std::shared_ptr<Aurora::VertexShader> vShader;
	std::shared_ptr<Aurora::PixelShader> pShader;
	std::shared_ptr<Aurora::IndexBuffer> iBuf;
	std::shared_ptr<Aurora::PixelConstantBuffer> pConst;
	std::shared_ptr<Aurora::InputLayout> iLayout;
	std::shared_ptr<Aurora::Topology> topology;
	std::shared_ptr<Aurora::VertexConstantBuffer> vConst;

	float x = -4.0f, y = 0.0f, z = 20.0f;
	float x1 = 0.0f, y1 = 0.0f, z1 = 0.0f;
	DirectX::XMMATRIX mat;
};

class Sandbox : public Aurora::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Aurora::Application* Aurora::CreateApplication()
{
	return new Sandbox();
}