#pragma once

#include "Platform/Windows/Graphics.h"
#include "Aurora/Renderer/Bindables.h"
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
		//void AddBind(std::unique_ptr<Bindable> bind) noexcept (!AU_DEBUG);
		void AddBind(std::shared_ptr<Bindables> bind) noexcept (!AU_DEBUG);
		void AddIndexBuffer(std::shared_ptr<class IndexBuffer> ibuf) noexcept(!AU_DEBUG);
		void ReplaceBindable(std::shared_ptr<Bindable> bindable);

	private:
		//virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept = 0;
		virtual const std::vector<std::shared_ptr<Bindables>>& GetStaticBindss() const noexcept = 0;
		class IndexBuffer* pIndexBuffer = nullptr;
		//std::vector<std::unique_ptr<Bindable>> binds;
		std::vector<std::shared_ptr<Bindables>> bindss;

	};
}