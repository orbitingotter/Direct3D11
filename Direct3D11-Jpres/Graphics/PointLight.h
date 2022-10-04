#pragma once

#include "Graphics.h"
#include "Graphics/Bindables/ConstantBuffer.h"
#include "Graphics/Drawables/SolidSphere.h"

class PointLight
{
public:
	PointLight(Graphics& gfx, float radius = 0.5f);
	void SpawnControlWindow() noexcept;
	void Reset() noexcept;
	void Draw(Graphics& gfx) const;
	void Bind(Graphics& gfx) const;
private:
	struct PointLightCBuf
	{
		DirectX::XMFLOAT3 pos;
		float padding;
	};
private:
	DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f };;
	mutable PixelConstantBuffer<PointLightCBuf> cbuf;
	mutable SolidSphere mesh;
};