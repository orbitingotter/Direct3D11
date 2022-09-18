#pragma once

#include "Graphics/Bindables/Bindable.h"
#include "Graphics/Bindables/IndexBuffer.h"
#include <DirectXMath.h>
#include <memory>
#include <vector>

class IndexBuffer;

class Drawable
{
	template<typename T>
	friend class DrawableBase;
public:
	void Draw(Graphics& gfx) const;

	virtual DirectX::XMMATRIX GetTransformXM() const = 0;
	virtual void Update(float dt) = 0;
	virtual ~Drawable() = default;

protected:
	void AddBind(std::unique_ptr<Bindable> bindable);
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> bindable);
private:
	virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const = 0;

private:
	std::vector <std::unique_ptr<Bindable>> mBinds;

protected:

	static UINT indexCount;
};