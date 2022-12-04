#include "Editorpch.h"
#include <Aurora.h>
#include <Aurora/Core/EntryPoint.h>
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
			}
			catch (const std::exception& e)
			{
				AU_CORE_FATAL("{0}", e.what());
			}
			catch (...)
			{
				AU_CORE_FATAL("No Details Available,Unknown Exception");
			}
		}
		~Editor()
		{

		}

	};


	Application* CreateApplication()
	{
		return new Editor();
	}

}

