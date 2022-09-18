#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics& gfx, std::vector<unsigned short> indices)
	:mCount((UINT)indices.size())
{
	D3D11_BUFFER_DESC ibd = {};
	ibd.ByteWidth = UINT(sizeof(unsigned short) * indices.size());
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = indices.data();

	GetDevice(gfx)->CreateBuffer(&ibd, &sd, &pIndexBuffer);
}

void IndexBuffer::Bind(Graphics& gfx)
{
	GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

UINT IndexBuffer::GetCount() const
{
	return mCount;
}
