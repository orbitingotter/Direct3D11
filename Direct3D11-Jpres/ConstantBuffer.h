#pragma once
#include "Bindable.h"

template<typename T>
class ConstantBuffer : public Bindable
{
public:
	ConstantBuffer(Graphics& gfx, const T& consts)
	{
		D3D11_BUFFER_DESC cbd = {};
		cbd.ByteWidth = sizeof(consts);
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0;
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = &consts;

		GetDevice(gfx)->CreateBuffer(&cbd, &sd, &pConstantBuffer);
	}

	void Update(Graphics& gfx, const T& consts)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetContext(gfx)->Map(pConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr);

		memcpy(msr.pData, &consts, sizeof(consts));

		GetContext(gfx)->Unmap(pConstantBuffer.Get(), 0u);
	}

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
};

template<typename T>
class VertexConstantBuffer : public ConstantBuffer<T>
{
	using Bindable::GetContext;
	using ConstantBuffer<T>::pConstantBuffer;
	using ConstantBuffer<T>::ConstantBuffer;
public:
	void Bind(Graphics& gfx) override
	{
		GetContext(gfx)->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};


template<typename T>
class PixelConstantBuffer : public ConstantBuffer<T>
{
	using Bindable::GetContext;
	using ConstantBuffer<T>::pConstantBuffer;
	using ConstantBuffer<T>::ConstantBuffer;
public:
	void Bind(Graphics& gfx) override
	{
		GetContext(gfx)->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};
