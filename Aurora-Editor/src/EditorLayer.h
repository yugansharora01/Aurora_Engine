#pragma once
#include <Aurora.h>

#include "Panels/SceneHierarchyPanel.h"
#include "Panels/GeometryPanel.h"

#include "imgui.h"
#include <DirectXMath.h>

#include <filesystem>


namespace Aurora {
	class D3D11Texture;

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual void OnImGuiRender() override;
		virtual void OnUpdate() override;
		virtual void OnAttach() override;
		virtual void OnEvent(Event& e) override;
		virtual void Init() override;
		void Panels();
		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveSceneAs();

	public:
		bool OnKeyPressed(KeyPressedEvent& e);
	private:
		int m_GuizmoType = -1;

		DirectX::XMFLOAT2 m_ViewportSize;
		DirectX::XMFLOAT2 m_ViewportPos;
		Ref<RenderTargetManager> TargetManager;

		Ref<Scene> m_activeScene;
		Ref<EditorCamera> m_editorCamera;

		Ref<SceneHierarchyPanel> m_sceneHeirarchyPanel;

		Ref<GeometryPanel> m_geometryPanel;
		Ref<D3D11Texture> TextTexture;
	};

}