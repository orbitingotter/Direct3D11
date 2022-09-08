#pragma once

#include "Bindable.h"
#include "IndexBuffer.h"
#include <DirectXMath.h>
#include <memory>
#include <vector>

class IndexBuffer;

class Drawable
{
public:
	void Draw(Graphics& gfx) const;
	void AddBind(std::unique_ptr<Bindable> bindable);
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> bindable);

	virtual DirectX::XMMATRIX GetTransformXM() const = 0;
	virtual void Update(float dt) = 0;
	virtual ~Drawable() = default;

private:
	UINT mIndexCount = 0u;
	std::vector <std::unique_ptr<Bindable>> mBinds;
};

