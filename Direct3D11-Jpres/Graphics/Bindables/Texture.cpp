#include "Texture.h"

#include "DirectXTK/WICTextureLoader.h"
#include "Utilities/StringConverter.h"
#include "Utilities/ErrorLogger.h"

Texture::Texture(Graphics& gfx, std::string fileName)
{

	HRESULT hr = DirectX::CreateWICTextureFromFile(GetDevice(gfx), StringConverter::StringToWide(fileName).c_str(),
		nullptr, pTextureView.GetAddressOf());

	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Cannot Load Texture : " + fileName + " from WICTextureLoader");
	}

}

void Texture::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());
}
