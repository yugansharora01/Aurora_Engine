#include "pch.h"
#include "Drawable.h"
#include "Bindable/IndexBuffer.h"
#include <cassert>
#include <typeinfo>

void Drawable::Draw(Graphics& gfx) const noexcept(!AU_DEBUG)
{
	for (auto& b : binds)
		b->Bind(gfx);

	for (auto& b : GetStaticBinds())
		b->Bind(gfx);

	gfx.DrawIndexed(pIndexBuffer->GetCount());
}

void Drawable::AddBind(std::unique_ptr<Bindable> bind) noexcept(!AU_DEBUG)
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

void Drawable::ReplaceBindable(std::unique_ptr<Bindable> bindable)
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
