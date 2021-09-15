#pragma once

#include "Aurora/Layer.h"
#include "Aurora/Core/AuTimer.h"

namespace Aurora {
	class ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;

	private:
		AuTimer timer;
		float m_Time = 0.0f;
	};
}