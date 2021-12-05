#pragma once
#include <Aurora.h>
#include "Aurora/Layer.h"

#include <DirectXMath.h>

#include "Panels/SceneHierarchyPanel.h"

#include "imgui.h"


namespace Aurora {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual void OnImGuiRender() override;
		virtual void OnUpdate() override;
		virtual void OnAttach() override;
		void Panels();
	private:

		DirectX::XMFLOAT2 m_ViewportSize;
		Ref<FrameBuffer> fBuffer;

		Ref<Scene> m_activeScene;

		Ref<SceneHierarchyPanel> m_sceneHeirarchyPanel;

		std::shared_ptr<VertexBuffer> vBuf;
		std::shared_ptr<VertexShader> vShader;
		std::shared_ptr<PixelShader> pShader;
		std::shared_ptr<IndexBuffer> iBuf;
		std::shared_ptr<EditorCamera> m_camera;


	};

}