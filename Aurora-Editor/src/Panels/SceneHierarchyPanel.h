#pragma once

#include <Aurora/Core.h>
#include <Aurora/Scene/ECS.h>
#include <Aurora/Scene/Scene.h>

namespace Aurora {
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(Ref<Scene> scene);
		~SceneHierarchyPanel();
		void SetScene(Ref<Scene> scene) { m_scene = scene; }

		void OnImGuiRender();

		void DrawEntityNode();
	private:
		Ref<Scene> m_scene;
	};

	
}