#pragma once

#include <DirectXMath.h>

namespace Aurora {

	class EditorCamera
	{
	public:
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);
		void UpdateProjection(float fov, float aspectRatio, float nearClip, float farClip);
		DirectX::XMMATRIX GetProjection() noexcept;
	private:
		DirectX::XMMATRIX m_proj;
		float m_fov;
		float m_aspectRatio;
		float m_nearClip;
		float m_farClip;
	};
}
