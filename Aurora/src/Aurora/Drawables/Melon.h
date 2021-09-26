#pragma once

#include "DrawableBase.h"

namespace Aurora {

	class Melon : public DrawableBase<Melon>
	{
	public:
		Melon(Graphics& gfx, int latdistp, int longdistp);
		void Update(float dt) noexcept override;
		DirectX::XMMATRIX GetTransformXM() const noexcept override;
		void SetMatrix(DirectX::XMMATRIX m) noexcept;

	private:

		DirectX::XMMATRIX mat;
	};
}
