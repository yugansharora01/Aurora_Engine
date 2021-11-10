#include <Aurora.h>
#include "EditorLayer.h"

namespace Aurora {


	class Editor : public Application
	{
	public:
		Editor()
		{
			try {
				PushLayer(new EditorLayer());
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
		~Editor()
		{

		}

	private:

	};


	Application* CreateApplication()
	{
		return new Editor();
	}

}

