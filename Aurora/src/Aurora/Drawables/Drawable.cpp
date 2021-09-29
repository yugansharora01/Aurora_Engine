#include "pch.h"
#include "Drawable.h"
#include "Aurora/Renderer/Buffer.h"
#include <cassert>
#include <typeinfo>

namespace Aurora {

	void Drawable::Draw(Graphics& gfx) const noexcept(!AU_DEBUG)
	{
		for (auto& b : binds)
			b->Bind();

		for (auto& b : GetStaticBinds())
			b->Bind();

		gfx.DrawIndexed(pIndexBuffer->GetCount());
	}

	void Drawable::AddBind(std::unique_ptr<Bindables> bind) noexcept(!AU_DEBUG)
	{
		assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
		binds.push_back(std::move(bind));
	}

	void Drawable::AddIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf) noexcept(!AU_DEBUG)
	{
		assert("Attempting to add index buuffer a second time" && pIndexBuffer == nullptr);
		pIndexBuffer = ibuf.get();
		binds.push_back(std::move(ibuf));
	}
}