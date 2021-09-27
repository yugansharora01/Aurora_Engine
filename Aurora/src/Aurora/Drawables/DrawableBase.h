#pragma once

#include "Drawable.h"
#include "Aurora/Renderer/Buffer.h"

namespace Aurora {

	template<class T>
	class DrawableBase : public Drawable
	{
	public:
		static bool IsStaticInitialized() noexcept
		{
			return !staticBinds.empty();
		}
		static void AddStaticBind(std::shared_ptr<Bindables> bind) noexcept (!AU_DEBUG)
		{
			assert("*Must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
			staticBinds.push_back(std::move(bind));
		}
		void AddStaticIndexBuffer(std::shared_ptr<IndexBuffer> ibuf) noexcept(!AU_DEBUG)
		{
			assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);
			pIndexBuffer = ibuf.get();
			staticBinds.push_back(std::move(ibuf));
		}
		void SetIndexFromStatic() noexcept(!AU_DEBUG)
		{
			assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);
			for (const auto& b : staticBinds)
			{
				if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
				{
					pIndexBuffer = p;
					return;
				}
			}
			assert("failed to find index buffer in static binds" && pIndexBuffer != nullptr);
		}
		void ReplaceStaticBindable(std::shared_ptr<Bindable> bindable)
		{
			//for (auto i = binds.begin(); i != binds.end(); i++)
			//{
			//	if (typeid(*bindable) == typeid(*i))
			//	{
			//		staticBinds.erase(i);
			//		staticBinds.insert(i, bindable);
			//	}
			//}
		}
	private:
		/*const std::vector<std::shared_ptr<Bindable>>& GetStaticBinds() const noexcept override
		{
			return staticBinds;
		}*/
		
		const std::vector<std::shared_ptr<Bindables>>& GetStaticBindss() const noexcept override
		{
			return staticBindss;
		}


	private:
		static std::vector<std::shared_ptr<Bindable>> staticBinds;
		static std::vector<std::shared_ptr<Bindables>> staticBindss;
	};

	template<class T>
	std::vector<std::shared_ptr<Bindable>> DrawableBase<T>::staticBinds;
	template<class T>
	std::vector<std::shared_ptr<Bindables>> DrawableBase<T>::staticBindss;
}