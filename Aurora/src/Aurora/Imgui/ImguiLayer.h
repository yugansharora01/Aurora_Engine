#pragma once

#include "Aurora/Core/Layer.h"
#include "Aurora/Core/AuTimer.h"

namespace Aurora {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void Init() override;

		void Begin();
		void End();
		//void DisplaySize();
		void SetDarkThemeColors();

	private:
		AuTimer timer;
		float m_Time = 0.0f;
	};
}