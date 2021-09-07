#include <Aurora.h>

class Sandbox : public Aurora::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Aurora::Application* Aurora::CreateApplication()
{
	return new Sandbox();
}