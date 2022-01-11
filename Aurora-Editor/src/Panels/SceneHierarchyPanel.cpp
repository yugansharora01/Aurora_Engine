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

		ImGui::Begin("Properties");

		if (m_selectedEntity)
			DrawComponents(m_selectedEntity);

		ImGui::End();
	}


	void SceneHierarchyPanel::DrawEntityNode(Ref<Entity> entity)
	{
		auto& tag = entity->GetComponent<TagComponent>()->tag;

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)*entity, flags, tag.c_str());

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
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

			bool opened = ImGui::TreeNodeEx((void*)1234, flags, tag.c_str());

			if (opened)
				ImGui::TreePop();

			ImGui::TreePop();
		}

		if (EntityDeleted)
		{
			m_scene->DestroyEntity(entity);
			if (m_selectedEntity == entity)
				m_selectedEntity = {};
		}

	}

	void SceneHierarchyPanel::DrawComponents(Ref<Entity> entity)
	{
		if (entity->HasComponent<TagComponent>())
		{
			auto& tag = entity->GetComponent<TagComponent>()->tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			std::strncpy(buffer, tag.c_str(), sizeof(buffer));

			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		if (entity->HasComponent<TransformComponent>())
		{
			auto c = entity->GetComponent<TransformComponent>();

			ImGui::Text("Translate");
			ImGui::DragFloat("##X", &c->translate.x, 0.1f, -50.0f, 50.0f, "%.2f");
			ImGui::DragFloat("##Y", &c->translate.y, 0.1f, -50.0f, 50.0f, "%.2f");
			ImGui::DragFloat("##Z", &c->translate.z, 0.1f, -50.0f, 50.0f, "%.2f");

			ImGui::Text("Rotation");
			ImGui::DragFloat("##X1", &c->rotation.x, 0.1f, -3.14f, 3.14f, "%.2f");
			ImGui::DragFloat("##Y1", &c->rotation.y, 0.1f, -3.14f, 3.14f, "%.2f");
			ImGui::DragFloat("##Z1", &c->rotation.z, 0.1f, -3.14f, 3.14f, "%.2f");
			
			ImGui::Text("Scale");
			ImGui::DragFloat("##X2", &c->scale.x, 0.1f, -10.0f, 10.0f, "%.2f");
			ImGui::DragFloat("##Y2", &c->scale.y, 0.1f, -10.0f, 10.0f, "%.2f");
			ImGui::DragFloat("##Z2", &c->scale.z, 0.1f, -10.0f, 10.0f, "%.2f");
		}

		if (entity->HasComponent<MeshComponent>())
		{
			auto c = entity->GetComponent<MeshComponent>();
			ImGui::Text("Color");
			ImGui::DragFloat("##X3", &c->color.x, 0.01f, 0.0f, 1.0f, "%.2f");
			ImGui::DragFloat("##Y3", &c->color.y, 0.01f, 0.0f, 1.0f, "%.2f");
			ImGui::DragFloat("##Z3", &c->color.z, 0.01f, 0.0f, 1.0f, "%.2f");
			
			ImGui::Text("Diffuse Color");
			ImGui::DragFloat("##X4", &c->diffuseColor.x, 0.01f, 0.0f, 1.0f, "%.2f");
			ImGui::DragFloat("##Y4", &c->diffuseColor.y, 0.01f, 0.0f, 1.0f, "%.2f");
			ImGui::DragFloat("##Z4", &c->diffuseColor.z, 0.01f, 0.0f, 1.0f, "%.2f");
			
			ImGui::Text("Diffuse Intensity");
			ImGui::DragFloat("##X5", &c->diffuseIntensity, 0.01f, 0.0f, 1.0f, "%.2f");
		}

		if (entity->HasComponent<LightComponent>())
		{
			auto c = entity->GetComponent<LightComponent>();

			ImGui::Text("attConst");
			ImGui::DragFloat("##X6", &c->attConst, 0.01f, 0.0f, 1.0f, "%.2f");
			
			ImGui::Text("attLin");
			ImGui::DragFloat("##X7", &c->attLin, 0.005f, 0.0f, 1.0f, "%.3f");
			
			ImGui::Text("attQuad");
			ImGui::DragFloat("##X8", &c->attQuad, 0.0005f, 0.0f, 1.0f, "%.4f");
		}
	}
}