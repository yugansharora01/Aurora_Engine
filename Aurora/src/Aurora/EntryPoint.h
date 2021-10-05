#pragma once

#ifdef AU_PLATFORM_WINDOWS


extern Aurora::Application* Aurora::CreateApplication();

int main(int argc,char** argv)
{

	Aurora::Log::Init();
	AU_CORE_WARN("Initialised Log!");
	int a = 5;
	AU_INFO("Hello! Var = {0}", a);

	auto app = Aurora::CreateApplication();
	app->Run();
	delete app;
	
	return 0;
}

#endif // AU_PLATFORM_WINDOWS

