#include "Topology.h"

Topology::Topology(D3D11_PRIMITIVE_TOPOLOGY type)
	: mType(type)
{
}

void Topology::Bind(Graphics& gfx)
{
	GetContext(gfx)->IASetPrimitiveTopology(mType);
}
