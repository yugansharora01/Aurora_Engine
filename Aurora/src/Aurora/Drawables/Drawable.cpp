#include "pch.h"
#include "Drawable.h"
#include "Aurora/Renderer/Buffer.h"
#include "Aurora/Log.h"
#include <cassert>
#include <typeinfo>

namespace Aurora {

	void Drawable::Draw(Graphics& gfx) const noexcept(!AU_DEBUG)
	{
		//for (auto& b : binds)
		//	b->Bind(gfx);

		for (auto& b : bindss)
			b->Bind();

		//for (auto& b : GetStaticBinds())
		//	b->Bind(gfx);
		
		for (auto& b : GetStaticBindss())
			b->Bind();

		gfx.DrawIndexed(pIndexBuffer->GetCount());
	}

	//void Drawable::AddBind(std::shared_ptr<Bindable> bind) noexcept(!AU_DEBUG)
	//{
	//	//assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
	//	binds.push_back(std::move(bind));
	//}

	void Drawable::AddBind(std::shared_ptr<Bindables> bind) noexcept(!AU_DEBUG)
	{
		assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
		bindss.push_back(std::move(bind));
	}

	void Drawable::AddIndexBuffer(std::shared_ptr<class IndexBuffer> ibuf) noexcept(!AU_DEBUG)
	{
		assert("Attempting to add index buuffer a second time" && pIndexBuffer == nullptr);
		pIndexBuffer = ibuf.get();
		bindss.push_back(std::move(ibuf));
	}

	void Drawable::ReplaceBindable(std::shared_ptr<Bindable> bindable)
	{
		//for (auto i = binds.begin(); i != binds.end(); i++)
		//{
		//	if (typeid(*bindable) == typeid(*i))
		//	{
		//		binds.erase(i);
		//		binds.insert(i, bindable);
		//	}
		//}
		//AddBind(&bindable);
	}
}
