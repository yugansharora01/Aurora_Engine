#pragma once

#include <DirectXMath.h>

namespace Aurora
{

	enum LightType
	{
		Point,
		Directional
	};

	struct LightInfo
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;

		LightType type;
	};

	

	class Light
	{
		friend class Renderer;
	public:
		Light() = default;
		Light(LightInfo info);
	private:
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
		LightType type;

	};
}


