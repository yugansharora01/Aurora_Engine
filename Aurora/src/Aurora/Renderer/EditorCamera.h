#pragma once

#include <DirectXMath.h>
#include <glm/glm.hpp>

namespace Aurora {

	class EditorCamera
	{
	public:
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);
		void UpdateProjection(float fov, float aspectRatio, float nearClip, float farClip);
		glm::mat4 GetProjection() noexcept;
	private:
		glm::mat4 m_proj;
		float m_fov;
		float m_aspectRatio;
		float m_nearClip;
		float m_farClip;
	};
}
