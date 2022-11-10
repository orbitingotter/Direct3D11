#pragma once

#include "Bindable.h"
#include <vector>

#include "Graphics/Vertex.h"

class VertexBuffer : public Bindable
{
public:
	template<typename T>
	VertexBuffer(Graphics& gfx, const std::vector<T>& vertices)
		: mStride(sizeof(T))
	{
		D3D11_BUFFER_DESC bd = {};
		bd.ByteWidth = UINT(vertices.size() * sizeof(T));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.StructureByteStride = sizeof(T);

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();

		GetDevice(gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer);
	}

	VertexBuffer(Graphics& gfx, const d3ddemo::VertexBuffer& vbuf)
		: mStride((UINT)vbuf.GetLayout().Size())
	{
		D3D11_BUFFER_DESC bd = {};
		bd.ByteWidth = UINT(vbuf.SizeBytes());
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.StructureByteStride = mStride;

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vbuf.GetData();

		GetDevice(gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer);
	}

	void Bind(Graphics& gfx) override;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	UINT mStride;
};
