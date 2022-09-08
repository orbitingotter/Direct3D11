#pragma once

#include "Bindable.h"
#include <vector>

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graphics& gfx, std::vector<unsigned short> indices);
	void Bind(Graphics& gfx) override;
	UINT GetCount() const;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	UINT mCount;
};

