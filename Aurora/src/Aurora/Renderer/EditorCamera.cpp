#include "pch.h"
#include "EditorCamera.h"
#include <glm/gtx/quaternion.hpp>
#include "Aurora/Log.h"

namespace Aurora {

	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		:m_fov(fov), m_aspectRatio(aspectRatio), m_nearClip(nearClip), m_farClip(farClip)
	{
		DirectX::XMMATRIX  l = DirectX::XMMatrixPerspectiveLH(fov, aspectRatio, nearClip, farClip);
		//m_proj = DirectX::XMMatrixPerspectiveLH(fov, aspectRatio, nearClip, farClip);
		m_proj = glm::perspective(35.0f,aspectRatio,nearClip,farClip);
		m_proj[0] = glm::vec4(0.0f,1.33f,0.0f,0.0f);
		m_proj[1] = glm::vec4(0.0f,0.0f,1.01f,1.0f);
		m_proj[2] = glm::vec4(0.0f,0.0f,-0.5f,0.0f);
		m_proj[3] = glm::vec4(0.0f,0.0f,-0.5f,0.0f);
		//if()
	}

	glm::mat4 EditorCamera::GetProjection() noexcept
	{
		return m_proj;
	}

	void EditorCamera::UpdateProjection(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_fov = fov; 
		m_aspectRatio = aspectRatio; 
		m_nearClip = nearClip; 
		m_farClip = farClip;
		m_proj[0] = glm::vec4(0.0f, 1.33f, 0.0f, 0.0f);
		m_proj[1] = glm::vec4(0.0f, 0.0f, 1.01f, 1.0f);
		m_proj[2] = glm::vec4(0.0f, 0.0f, -0.5f, 0.0f);
		m_proj[3] = glm::vec4(0.0f, 0.0f, -0.5f, 0.0f);
		//m_proj = DirectX::XMMatrixPerspectiveLH(m_fov, m_aspectRatio, m_nearClip, m_farClip);
		//m_proj = glm::perspective(m_fov, m_aspectRatio, m_nearClip, m_farClip);
	}

}