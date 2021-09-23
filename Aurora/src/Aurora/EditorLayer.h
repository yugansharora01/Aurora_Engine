#pragma once

#include "Aurora/Layer.h"


namespace Aurora {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer() = default;
		void Get(float &Red, float &Green, float &Blue);
		void GetPos(float & x, float & y, float & z);
		virtual void OnImGuiRender() override;
	private:
		float red;
		float green;
		float blue;
		float x = -4.0f;
		float y;
		float z = 20.0f;
	};

}