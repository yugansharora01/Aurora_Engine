#pragma once

#pragma once
#include "DrawableBase.h"

namespace Aurora {

	class SkinnedBox : public DrawableBase<SkinnedBox>
	{
	public:
		SkinnedBox(Graphics& gfx);
		void Update(float dt) noexcept override;
		DirectX::XMMATRIX GetTransformXM() const noexcept override;
		void SetMatrix(DirectX::XMMATRIX m) noexcept;

	private:
		DirectX::XMMATRIX mat;

	};
}