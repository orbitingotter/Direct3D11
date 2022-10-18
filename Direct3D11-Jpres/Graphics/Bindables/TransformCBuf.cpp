#include "TransformCbuf.h"

std::unique_ptr<VertexConstantBuffer<TransformCBuf::Transforms>> TransformCBuf::pVcbuf;

TransformCBuf::TransformCBuf(Graphics& gfx, const Drawable& parent)
	:
	parent(parent)
{
	if (!pVcbuf)
	{
		pVcbuf = std::make_unique<VertexConstantBuffer<Transforms>>(gfx);
	}
}

void TransformCBuf::Bind(Graphics& gfx) noexcept
{
	const auto model = parent.GetTransformXM();
	const Transforms tf =
	{
		DirectX::XMMatrixTranspose(model),
		DirectX::XMMatrixTranspose(model * gfx.GetCamera()),
		DirectX::XMMatrixTranspose(model * gfx.GetCamera() * gfx.GetProjection())
	};

	pVcbuf->Update(gfx, tf);
	pVcbuf->Bind(gfx);
}