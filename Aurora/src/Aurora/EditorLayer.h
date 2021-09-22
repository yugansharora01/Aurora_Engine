#pragma once

#include "Aurora/Layer.h"


namespace Aurora {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer() = default;
		void Get(float &Red, float &Green, float &Blue);
		virtual void OnImGuiRender() override;
	private:
		float red;
		float green;
		float blue;
	};

}