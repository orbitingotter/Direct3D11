#pragma once

#include "Bindable.h"
#include <string>

class VertexShader : public Bindable
{
public:
	VertexShader(Graphics& gfx, const std::string& path);
	void Bind(Graphics& gfx) override;
	ID3DBlob* GetByteCode() const;

private:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;

};

