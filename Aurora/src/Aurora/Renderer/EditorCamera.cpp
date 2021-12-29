#include "pch.h"
#include "EditorCamera.h"
#include "Aurora/Log.h"
#include "Aurora/Core/Input.h"

namespace Aurora {

	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		:m_fov(fov), m_aspectRatio(aspectRatio), m_nearClip(nearClip), m_farClip(farClip)
	{
		MoveSpeed = 0.5f;
		RotationSpeed = 0.1f;

		translate = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);

		DirectX::XMFLOAT4 zerofloat( 0.0f,0.0f,0.0f,0.0f );
		auto zeroVec = DirectX::XMLoadFloat4(&zerofloat);
		DirectX::XMFLOAT4 identityQuatFloat( 1.0f,0.0f,0.0f,0.0f );
		auto identityQuat = DirectX::XMLoadFloat4(&identityQuatFloat);
		auto scaleVec = DirectX::XMLoadFloat3(&scale);
		auto translateVec = DirectX::XMLoadFloat3(&translate);
		auto rotationVec = DirectX::XMLoadFloat3(&rotation);

		transform = DirectX::XMMatrixTransformation(zeroVec, identityQuat, scaleVec, zeroVec, DirectX::XMQuaternionRotationRollPitchYawFromVector(rotationVec), translateVec);
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

		bool control = Input::IsKeyPressed(Key::Control);
		bool shift = Input::IsKeyPressed(Key::Shift);

		switch (e.GetKeyCode())
		{
		case Key::W :
			if(!control && !shift)
				rotation.x += RotationSpeed;
			break;
		case Key::A :
			if (!control && !shift)
				rotation.y += RotationSpeed;
			break;
		case Key::S :
			if (!control && !shift)
				rotation.x -= RotationSpeed;
			break;
		case Key::D :
			if (!control && !shift)
				rotation.y -= RotationSpeed;
			break;
		case Key::UpArrow :
			if (!control && !shift)
				translate.z += MoveSpeed;
			break;
		case Key::DownArrow :
			if (!control && !shift)
				translate.z -= MoveSpeed;
			break;
		case Key::LeftArrow :
			if (!control && !shift)
				translate.x -= MoveSpeed;
			break;
		case Key::RightArrow :
			if (!control && !shift)
				translate.x += MoveSpeed;
			break;
		default:
			break;
		}

		DirectX::XMFLOAT4 zerofloat(0.0f, 0.0f, 0.0f, 0.0f);
		auto zeroVec = DirectX::XMLoadFloat4(&zerofloat);
		DirectX::XMFLOAT4 identityQuatFloat(1.0f, 0.0f, 0.0f, 0.0f);
		auto identityQuat = DirectX::XMLoadFloat4(&identityQuatFloat);
		auto scaleVec = DirectX::XMLoadFloat3(&scale);
		auto translateVec = DirectX::XMLoadFloat3(&translate);
		auto rotationVec = DirectX::XMLoadFloat3(&rotation);

		transform = DirectX::XMMatrixTransformation(zeroVec, identityQuat, scaleVec, zeroVec, DirectX::XMQuaternionRotationRollPitchYawFromVector(rotationVec), translateVec);

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