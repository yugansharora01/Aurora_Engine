#include <Aurora.h>
#include <vector>

#include <Platform/Windows/Win32_Window.h>


class ExampleLayer : public Aurora::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
		
		DirectX::XMFLOAT3 pos;
		
		const auto model = Cube::Make<DirectX::XMFLOAT3>();

		vBuf = Aurora::VertexBuffer::Create(model.vertices);

		vShader = Aurora::VertexShader::Create(L"../bin/Debug-windows-x86_64/Aurora/ColorIndexVS.cso");

		pShader = Aurora::PixelShader::Create(L"../bin/Debug-windows-x86_64/Aurora/ColorIndexPS.cso");
		
		iBuf = Aurora::IndexBuffer::Create(model.indices);

		std::array<DirectX::XMFLOAT4, 8> face_colors =
		{
			{
				{ 1.0f,1.0f,1.0f,1.0f },
				{ 1.0f,0.0f,0.0f,1.0f },
				{ 0.0f,1.0f,0.0f,1.0f },
				{ 1.0f,1.0f,0.0f,1.0f },
				{ 0.0f,0.0f,1.0f,1.0f },
				{ 1.0f,0.0f,1.0f,1.0f },
				{ 0.0f,1.0f,1.0f,1.0f },
				{ 0.0f,0.0f,0.0f,1.0f },
			}
		};
		pShader->UploadMat4X8(face_colors);

		std::vector<Aurora::LayoutBuffer> list;

		list.emplace_back("Position", 0u, Aurora::ShaderDataType::Float3, false, 32);
		

		vBuf->SetLayout(list,vShader);

		vBuf->SetTopology(Aurora::TopologyType::Triangle_List);

		m_camera = std::make_shared<Aurora::EditorCamera>(1, 3.0f / 4.0f, 0.5f, 40.0f);
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("box");

		ImGui::SliderFloat("x", &x, -100.0f, 100.0f);
		ImGui::SliderFloat("y", &y, -100.0f, 100.0f);
		ImGui::SliderFloat("z", &z, -100.0f, 100.0f);
		
		ImGui::SliderFloat("x-axis", &x1, -3.14f, 3.14f);
		ImGui::SliderFloat("y-axis", &y1, -3.14f, 3.14f);
		ImGui::SliderFloat("z-axis", &z1, -3.14f, 3.14f);

		//ImGui::SliderFloat4("Face1", Face1, 0.0f, 1.0f);
		//ImGui::SliderFloat4("Face2", Face2, 0.0f, 1.0f);
		//ImGui::SliderFloat4("Face3", Face3, 0.0f, 1.0f);
		//ImGui::SliderFloat4("Face4", Face4, 0.0f, 1.0f);
		//ImGui::SliderFloat4("Face5", Face5, 0.0f, 1.0f);
		//ImGui::SliderFloat4("Face6", Face6, 0.0f, 1.0f);
		//ImGui::SliderFloat4("Face7", Face7, 0.0f, 1.0f);
		//ImGui::SliderFloat4("Face8", Face8, 0.0f, 1.0f);

		ImGui::End();
	}

	/*std::array<DirectX::XMFLOAT4, 8> GetColor()
	{
		
		std::array<DirectX::XMFLOAT4, 8> face_colors =
		{
			{
				{ Face1[0] ,Face1[1] ,Face1[2] , Face1[3] },
				{ Face2[0] ,Face2[1] ,Face2[2] , Face2[3] },
				{ Face3[0] ,Face3[1] ,Face3[2] , Face3[3] },
				{ Face4[0] ,Face4[1] ,Face4[2] , Face4[3] },
				{ Face5[0] ,Face5[1] ,Face5[2] , Face5[3] },
				{ Face6[0] ,Face6[1] ,Face6[2] , Face6[3] },
				{ Face7[0] ,Face7[1] ,Face7[2] , Face7[3] },
				{ Face8[0] ,Face8[1] ,Face8[2] , Face8[3] }
			}
		};
		return face_colors;
	}*/
	
	void OnUpdate() override
	{
		//unsigned int width = 0, height = 0;
		//auto wnd = (Aurora::Win32_Window*)Aurora::Application::Get().GetWindow().GetNativeWindowPtr();
		//wnd->GetWindowSize(width, height);
		auto height = Aurora::Application::Get().GetWindow().GetHeight();
		auto width = Aurora::Application::Get().GetWindow().GetWidth();
		m_camera->UpdateProjection(1, (float)height / (float)width, 0.5f,40.0f);

		
		vShader->UploadMat4(DirectX::XMMatrixTranspose(
			GetMatrix() * m_camera->GetProjection()));

		//pShader->UploadMat4X8(GetColor());

		Aurora::Renderer::BeginScene();

		Aurora::Renderer::Submit(vShader, pShader, vBuf, iBuf);

		Aurora::Renderer::EndScene();

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
	std::shared_ptr<Aurora::EditorCamera> m_camera;

	float x = -4.0f, y = 0.0f, z = 20.0f;
	float x1 = 0.0f, y1 = 0.0f, z1 = 0.0f;
	

	//float Face1[4], Face2[4], Face3[4], Face4[4], Face5[4], Face6[4], Face7[4], Face8[4];

	DirectX::XMMATRIX mat;
};

class Sandbox : public Aurora::Application
{
public:
	Sandbox()
	{
		try {
			PushLayer(new ExampleLayer());
		}
		catch (const Aurora::AuroraException& e)
		{
			AU_CORE_FATAL("{0}", e.what());
			MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
		}
		catch (const std::exception& e)
		{
			MessageBoxA(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
		}
		catch (...)
		{
			MessageBoxA(nullptr, "No Details Available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
		}
	}
	~Sandbox()
	{

	}
};

Aurora::Application* Aurora::CreateApplication()
{
	return new Sandbox();
}