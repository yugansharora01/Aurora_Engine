#include "Editorpch.h"
#include "SceneHierarchyPanel.h"
#include "Aurora/Scene/Components.h"
#include "imgui.h"

namespace Aurora {
	SceneHierarchyPanel::SceneHierarchyPanel(Ref<Scene> scene)
		:m_scene(scene)
	{
	}
	SceneHierarchyPanel::~SceneHierarchyPanel()
	{
	}
	void SceneHierarchyPanel::OnImGuiRender()
	{
		auto entities = m_scene->registry->GetList();

		ImGui::Begin("SceneHeirarchyPanel");
		
		for (size_t i = 0; i < entities.size(); i++)
		{
			DrawEntityNode(entities[i]);
		}

		ImGui::End();
	}
	void SceneHierarchyPanel::DrawEntityNode(Ref<Entity> entity)
	{
		auto& tag = entity->GetComponent<TagComponent>()->tag;

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

		bool opened = ImGui::TreeNodeEx((void*)(uint32_t)*entity, flags, tag.c_str());

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

			bool opened = ImGui::TreeNodeEx((void*)1234, flags, tag.c_str());

			if (ImGui::IsItemClicked())
			{
				m_selectedEntity = entity;
			}

			bool EntityDeleted = false;
			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::MenuItem("Delete Entity"))
					EntityDeleted = true;

				ImGui::EndPopup();
			}

			if (opened)
				ImGui::TreePop();

			ImGui::TreePop();

			if (EntityDeleted)
			{
				m_scene->DestroyEntity(entity);
				if (m_selectedEntity == entity)
					m_selectedEntity = {};
			}
		}

	}
}