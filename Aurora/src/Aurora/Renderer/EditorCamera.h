#pragma once

#include <DirectXMath.h>
#include "Aurora/Events/Events.h"
#include "Aurora/Events/KeyboardEvents.h"

namespace Aurora {

	class Camera
	{
	public:
		DirectX::XMFLOAT3 translate;
		DirectX::XMFLOAT3 rotation;
		DirectX::XMFLOAT3 scale;
	public:
		Camera(float fov, float aspectRatio, float nearClip, float farClip);
		void UpdateProjection(float fov, float aspectRatio, float nearClip, float farClip);
		void UpdateTransform(DirectX::XMMATRIX TransformMat);
		DirectX::XMMATRIX GetProjection() noexcept;
		DirectX::XMMATRIX GetTransform() noexcept;

		bool OnEvent(Event& e);
		bool OnKeyPressed(KeyPressedEvent& e);
	private:
		DirectX::XMMATRIX transform;
		DirectX::XMMATRIX m_proj;

		float MoveSpeed;
		float RotationSpeed;
		float m_fov;
		float m_aspectRatio;
		float m_nearClip;
		float m_farClip;
	};

	class EditorCamera : public Camera
	{
	public:
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
			:Camera(fov, aspectRatio, nearClip, farClip){}
	};
}
