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
			ImGui::DragFloat("##ROT-X", &c->rotation.x, 0.1f, -3.14f, 3.14f, "%.2f");
			ImGui::DragFloat("##ROT-Y", &c->rotation.y, 0.1f, -3.14f, 3.14f, "%.2f");
			ImGui::DragFloat("##ROT-Z", &c->rotation.z, 0.1f, -3.14f, 3.14f, "%.2f");
			
			ImGui::Text("Scale");
			ImGui::DragFloat("##SCA-X", &c->scale.x, 0.1f, -10.0f, 10.0f, "%.2f");
			ImGui::DragFloat("##SCA-Y", &c->scale.y, 0.1f, -10.0f, 10.0f, "%.2f");
			ImGui::DragFloat("##SCA-Z", &c->scale.z, 0.1f, -10.0f, 10.0f, "%.2f");
		}

		if (entity->HasComponent<MeshComponent>())
		{
			auto c = entity->GetComponent<MeshComponent>();
			ImGui::Text("Color");
			ImGui::ColorEdit4("##Color", &c->color.x);

			ImGui::Text("Specular Intensity");
			ImGui::DragFloat("##SpecularIntensity", &c->specularIntensity, 0.01f, 0.0f, 1.0f, "%.2f");

			ImGui::Text("Specular Power");
			ImGui::DragFloat("##SpecularPower", &c->specularPower, 1.0f, 0.0f, 100.0f, "%.2f");

			//ImGui::DragInt
			
		}

		if (entity->HasComponent<LightComponent>())
		{
			auto c = entity->GetComponent<LightComponent>();

			ImGui::Text("Ambient");
			ImGui::ColorEdit4("##AmbientColor", &c->ambient.x);

			ImGui::Text("Diffuse Color");
			ImGui::ColorEdit4("##DiffuseColor", &c->diffuseColor.x);

			ImGui::Text("Diffuse Intensity");
			ImGui::DragFloat("##X5", &c->diffuseIntensity, 0.01f, 0.0f, 1.0f, "%.2f");

			ImGui::Text("attConst");
			ImGui::DragFloat("##X6", &c->attConst, 0.01f, 0.0f, 1.0f, "%.2f");
			
			ImGui::Text("attLin");
			ImGui::DragFloat("##X7", &c->attLin, 0.005f, 0.0f, 1.0f, "%.3f");
			
			ImGui::Text("attQuad");
			ImGui::DragFloat("##X8", &c->attQuad, 0.0005f, 0.0f, 1.0f, "%.4f");
		}
	}
}