#pragma once

#include "Graphics.h"
#include <d3d11.h>

class Bindable
{
public:
	virtual void Bind(Graphics& gfx) = 0;
	virtual ~Bindable() = default;

protected:
	static ID3D11Device* GetDevice(Graphics& gfx);
	static ID3D11DeviceContext* GetContext(Graphics& gfx);

};

