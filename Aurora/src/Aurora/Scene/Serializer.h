#pragma once

#include "Aurora.h"

namespace Aurora
{
	class Serializer
	{
	public:
		Serializer(Ref<Scene> scene);
		~Serializer() = default;

		void Serialize();
		void Serialize(std::string file);

		bool Deserialize();
		bool Deserialize(std::string file);

	private:
		Ref<Scene> m_scene;
	};

}