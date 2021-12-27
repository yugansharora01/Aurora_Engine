#include "pch.h"
#include "EditorCamera.h"
#include "Aurora/Log.h"

namespace Aurora {

	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		:m_fov(fov), m_aspectRatio(aspectRatio), m_nearClip(nearClip), m_farClip(farClip)
	{
		MoveSpeed = 0.5f;
		RotationSpeed = 0.1f;

		translate = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

		transform = DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) *
			DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	}

	DirectX::XMMATRIX EditorCamera::GetProjection() noexcept
	{
		return m_proj;
	}

	DirectX::XMMATRIX EditorCamera::GetTransform() noexcept
	{
		return transform;
	}

	bool EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(AURORA_BIND_EVENT_FN(EditorCamera::OnKeyPressed));

		return false;
	}

	bool EditorCamera::OnKeyPressed(KeyPressedEvent& e)
	{
		AU_INFO("KeyPressed : {0}", (int)e.GetKeyCode());
		switch (e.GetKeyCode())
		{
		case Key::W :
			rotation.x += RotationSpeed;
			break;
		case Key::A :
			rotation.y += RotationSpeed;
			break;
		case Key::S :
			rotation.x -= RotationSpeed;
			break;
		case Key::D :
			rotation.y -= RotationSpeed;
			break;
		case Key::UpArrow :
			translate.z += MoveSpeed;
				break;
		case Key::DownArrow :
			translate.z -= MoveSpeed;
				break;
		case Key::LeftArrow :
			translate.x -= MoveSpeed;
				break;
		case Key::RightArrow :
			translate.x += MoveSpeed;
				break;
		default:
			break;
		}

		auto x = translate.x;
		auto y = translate.y;
		auto z = translate.z;
		auto x1 = rotation.x;
		auto y1 = rotation.y;
		auto z1 = rotation.z;

		transform = DirectX::XMMatrixRotationRollPitchYaw(x1, y1, z1) *
			DirectX::XMMatrixTranslation(x, y, z);

		return false;
	}

	void EditorCamera::UpdateProjection(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_fov = fov; 
		m_aspectRatio = aspectRatio; 
		m_nearClip = nearClip; 
		m_farClip = farClip;
		m_proj = DirectX::XMMatrixPerspectiveLH(m_fov, m_aspectRatio, m_nearClip, m_farClip);
	}

	void EditorCamera::UpdateTransform(DirectX::XMMATRIX TransformMat)
	{
		transform = TransformMat;
	}

}