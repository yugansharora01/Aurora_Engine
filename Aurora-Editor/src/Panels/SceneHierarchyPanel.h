#pragma once

#include "Aurora/Core.h"
#include "Aurora/Scene/ECS.h"
#include "Aurora/Scene/Scene.h"

namespace Aurora {
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(Ref<Scene> scene);
		~SceneHierarchyPanel();
		void SetScene(Ref<Scene> scene) { m_scene = scene; }

		void OnImGuiRender();

		void DrawEntityNode(Ref<Entity> entity);

		void DrawComponents(Ref<Entity> entity);

		Ref<Entity> GetSelectedEntity() { return m_selectedEntity; }


	private:
		Ref<Scene> m_scene;
		Ref<Entity> m_selectedEntity;
	};

	
}