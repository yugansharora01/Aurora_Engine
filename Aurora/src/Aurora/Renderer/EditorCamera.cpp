#include "pch.h"
#include "EditorCamera.h"

namespace Aurora {

	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		:m_fov(fov), m_aspectRatio(aspectRatio), m_nearClip(nearClip), m_farClip(farClip)
	{
		m_proj = DirectX::XMMatrixPerspectiveLH(fov, aspectRatio, nearClip, farClip);
	}

	DirectX::XMMATRIX EditorCamera::GetProjection() noexcept
	{
		return m_proj;
	}

	void EditorCamera::UpdateProjection()
	{
		m_proj = DirectX::XMMatrixPerspectiveLH(m_fov, m_aspectRatio, m_nearClip, m_farClip);
	}

}