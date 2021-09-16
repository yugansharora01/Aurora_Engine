#pragma once

#include "DrawableBase.h"
#include <random>

class Box : public DrawableBase<Box>
{
public:
	Box(Graphics& gfx);
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void SetMatrix(DirectX::XMMATRIX m) noexcept;
	void Update(float dt) noexcept override;
	void SetColor(Graphics& gfx);
private:
	
	//model transform
	DirectX::XMFLOAT3X3 mt;

	DirectX::XMMATRIX mat;
};
