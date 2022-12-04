#pragma once

#include "Aurora/Core/Core.h"
#include "Aurora/Scene/ECS.h"
#include "Aurora/Scene/Scene.h"

namespace Aurora
{
	class GeometryPanel
	{
	public:
		GeometryPanel() = default;
		GeometryPanel(Ref<Scene> scene)
			:m_scene(scene) {}
		~GeometryPanel() {}
		void SetScene(Ref<Scene> scene) { m_scene = scene; }

		void OnImGuiRender();

		void DrawGeometry();


	private:
		Ref<Scene> m_scene;
		Ref<Entity> m_selectedEntity;
	};
}