#include "Drawable.h"

void Drawable::Draw(Graphics& gfx) const
{
	for (auto& b : mBinds)
	{
		b->Bind(gfx);
	}


	gfx.DrawIndexed(mIndexCount);
}

void Drawable::AddBind(std::unique_ptr<Bindable> bindable)
{
	mBinds.push_back(std::move(bindable));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> bindable)
{
	mIndexCount = bindable->GetCount();
	mBinds.push_back(std::move(bindable));
}
