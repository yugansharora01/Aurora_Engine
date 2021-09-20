#pragma once

#include "DrawableBase.h"

class Sheet : public DrawableBase<Sheet>
{
public:
	Sheet(Graphics& gfx,std::string name);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void SetMatrix(DirectX::XMMATRIX m) noexcept;
	std::string name;
private:
	DirectX::XMMATRIX mat;
};