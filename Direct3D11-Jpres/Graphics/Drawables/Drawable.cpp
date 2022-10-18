#include "Drawable.h"
#include <memory>
#include <Graphics/Bindables/IndexBuffer.h>

UINT Drawable::indexCount = 0;

void Drawable::Draw(Graphics& gfx) const
{
	for (auto& b : mBinds)
	{
		if (auto const iBufRef = dynamic_cast<IndexBuffer*>(b.get()))
		{
			indexCount = iBufRef->GetCount();
		}
		b->Bind(gfx);
	}

	for (auto& b : GetStaticBinds())
	{
		if (auto const iBufRef = dynamic_cast<IndexBuffer*>(b.get()))
		{
			indexCount = iBufRef->GetCount();
		}

		b->Bind(gfx);
	}

	gfx.DrawIndexed(indexCount);
}

void Drawable::AddBind(std::unique_ptr<Bindable> bindable)
{
	mBinds.push_back(std::move(bindable));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> bindable)
{
	//indexCount = bindable->GetCount();
	mBinds.push_back(std::move(bindable));
}
