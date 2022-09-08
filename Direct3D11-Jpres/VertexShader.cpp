#include "VertexShader.h"
#include "StringConverter.h"

#include <d3dcompiler.h>

VertexShader::VertexShader(Graphics& gfx, const std::string& path)
{
	D3DReadFileToBlob(StringConverter::StringToWide(path).c_str(), &pBlob);
	GetDevice(gfx)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
}

void VertexShader::Bind(Graphics& gfx)
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetByteCode() const
{
	return pBlob.Get();
}
