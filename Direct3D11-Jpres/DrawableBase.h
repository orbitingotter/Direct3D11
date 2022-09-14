#pragma once

#include "Drawable.h"

template<typename T>
class DrawableBase : public Drawable
{
protected:

	bool IsStaticInitialized() const
	{
		return !mStaticBinds.empty();
	}

	static void AddStaticBind(std::unique_ptr<Bindable> bindable)
	{
		mStaticBinds.push_back(std::move(bindable));
	}

	static void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> bindable)
	{
		indexCount = bindable->GetCount();
		mStaticBinds.push_back(std::move(bindable));
	}

private:
	const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const override
	{
		return mStaticBinds;
	}

	static std::vector<std::unique_ptr<Bindable>> mStaticBinds;
};

template<typename T>
std::vector<std::unique_ptr<Bindable>> DrawableBase<T>::mStaticBinds;