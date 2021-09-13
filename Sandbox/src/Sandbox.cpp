#include <Aurora.h>

class ExampleLayer : public Aurora::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}
	
	void OnUpdate() override
	{
		AU_INFO("ExampleLayer::Update");
	}

	void OnEvent(Aurora::Event& event) override
	{
		AU_TRACE("{0}", event);
	}

private:

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