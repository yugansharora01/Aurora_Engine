#pragma once

#include "Platform/Windows/Graphics.h"
#include <DirectXMath.h>

namespace Aurora {

	class Bindable;

	class Drawable
	{
		template<class T>
		friend class DrawableBase;
	public:
		Drawable() = default;
		Drawable(const Drawable&) = delete;
		virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;
		void Draw(Graphics& gfx) const noexcept(!AU_DEBUG);
		virtual void Update(float dt) noexcept = 0;
		virtual ~Drawable() = default;
	protected:
		void AddBind(std::unique_ptr<Bindable> bind) noexcept (!AU_DEBUG);
		void AddIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf) noexcept(!AU_DEBUG);
		void ReplaceBindable(std::unique_ptr<Bindable> bindable);

	private:
		virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept = 0;
		const class IndexBuffer* pIndexBuffer = nullptr;
		std::vector<std::unique_ptr<Bindable>> binds;

	};
}