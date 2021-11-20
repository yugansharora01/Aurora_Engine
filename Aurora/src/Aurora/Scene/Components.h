#pragma once
#include "ECS.h"

namespace Aurora {
	struct TagComponent : public Component
	{
	public:
		std::string tag;
	public:
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& str)
			:tag(str){}
		~TagComponent(){}
		virtual void OnComponentAdd() override {}
		virtual void update() override {}
	};

}