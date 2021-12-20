#pragma once

#include "Aurora/Core.h"
#include "Aurora/Events/Events.h"

namespace Aurora {
	class AURORA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender(){}
		virtual void OnEvent(Event& event) {}
		virtual void Init() {}

		inline const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};

	
}
