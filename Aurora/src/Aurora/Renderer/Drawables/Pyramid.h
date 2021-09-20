#pragma once

#include "DrawableBase.h"

class Pyramid : public DrawableBase<Pyramid>
{
public:
	Pyramid(Graphics& gfx);
	void Update(float dt) noexcept override;
	
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void SetMatrix(DirectX::XMMATRIX m) noexcept;

private:

	DirectX::XMMATRIX mat;
};