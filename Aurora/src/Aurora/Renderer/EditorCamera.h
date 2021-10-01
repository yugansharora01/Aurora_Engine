#pragma once

#include <DirectXMath.h>

class EditorCamera
{
public:
	EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);
	DirectX::XMMATRIX GetProjection();
	void UpdateProjection();
private:
	DirectX::XMMATRIX m_proj;
	float m_fov;
	float m_aspectRatio;
	float m_nearClip;
	float m_farClip;
};

