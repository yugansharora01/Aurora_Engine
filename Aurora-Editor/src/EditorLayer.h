#pragma once
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

#include <DirectXMath.h>

namespace Aurora {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer() = default;
		void Get(float &Red, float &Green, float &Blue);
		void GetPos(float & x, float & y, float & z);
		virtual void OnImGuiRender() override;
	private:
		float red = 0.01f;
		float green = 0.01f;
		float blue = 0.01f;
		float x = -4.0f;
		float y = 0.0f;
		float z = 20.0f;

		std::vector<int> lastwindowposition;
	};

}