#include "PixelShader.h"
#include "StringConverter.h"

#include <d3dcompiler.h>

PixelShader::PixelShader(Graphics& gfx, std::string path)
{
	D3DReadFileToBlob(StringConverter::StringToWide(path).c_str(), &pBlob);
	GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
}

void PixelShader::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
