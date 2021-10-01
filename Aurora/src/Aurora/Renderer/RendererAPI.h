#pragma once

namespace Aurora {

	class RendererAPI
	{
	public:
		enum class API
		{
			Direct3D = 0,openGL = 1
		};
		static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};

}