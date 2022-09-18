#pragma once

#include "Graphics/Bindables/ConstantBuffer.h"
#include "Graphics/Drawables/Drawable.h"
#include <DirectXMath.h>

class TransformCBuf : public Bindable
{
public:
	TransformCBuf(Graphics& gfx, const Drawable& parent);
	void Bind(Graphics& gfx) noexcept override;

private:
	static std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> pVcbuf;
	const Drawable& parent;
};