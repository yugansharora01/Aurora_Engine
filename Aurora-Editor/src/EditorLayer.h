#pragma once
#include <Aurora.h>
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <queue>
#include <bitset>
#include <optional>
#include "Aurora/Layer.h"

#include <glm/glm.hpp>
#include <DirectXMath.h>
#include "imgui.h"

namespace Aurora {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual void OnImGuiRender() override;
		virtual void OnUpdate() override;
		virtual void OnAttach() override;
		DirectX::XMMATRIX GetMatrix();
		void Panels();
	private:
		glm::vec4 color;

		glm::vec2 m_ViewportSize;
		Ref<FrameBuffer> fBuffer;

		std::shared_ptr<Aurora::VertexBuffer> vBuf;
		std::shared_ptr<Aurora::VertexShader> vShader;
		std::shared_ptr<Aurora::PixelShader> pShader;
		std::shared_ptr<Aurora::IndexBuffer> iBuf;
		std::shared_ptr<Aurora::EditorCamera> m_camera;

		float x = -4.0f, y = 0.0f, z = 20.0f;
		float x1 = 0.0f, y1 = 0.0f, z1 = 0.0f;


		//float Face1[4], Face2[4], Face3[4], Face4[4], Face5[4], Face6[4], Face7[4], Face8[4];

		DirectX::XMMATRIX mat;

	};

}