#include "Graphics.h"
#include "Utilities/ErrorLogger.h"

#include <math.h>
#include <vector>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>

#include "Graphics/Bindables/BindableIncludes.h"
#include "Graphics/Drawables/Drawable.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"



using namespace Microsoft::WRL;

Graphics::~Graphics()
{
	ImGui_ImplDX11_Shutdown();
}

bool Graphics::Initialize(HWND hWnd, int width, int height)
{

	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0u;

	HRESULT hr;

	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0u, D3D11_SDK_VERSION,
		&sd, &pSwap, &pDevice, nullptr, &pContext);

	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to Initialized D3D11 Device and Swap Chain");
		return false;
	}


	ComPtr<ID3D11Resource> pBackBuffer;
	hr = pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to Get Buffer from Swap Chain");
		return false;
	}

	hr = pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget);
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to Create Render Target View");
		return false;
	}

	// Create Depth Buffer
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	ComPtr<ID3D11DepthStencilState> pDSState;

	pDevice->CreateDepthStencilState(&dsDesc, &pDSState);
	pContext->OMSetDepthStencilState(pDSState.Get(), 1u);

	ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC tDesc = {};
	tDesc.Width = width;
	tDesc.Height = height;
	tDesc.MipLevels = 1u;
	tDesc.ArraySize = 1u;
	tDesc.Format = DXGI_FORMAT_D32_FLOAT;
	tDesc.SampleDesc.Count = 1u;
	tDesc.SampleDesc.Quality = 0u;
	tDesc.Usage = D3D11_USAGE_DEFAULT;
	tDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	pDevice->CreateTexture2D(&tDesc, nullptr, &pDepthStencil);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Flags = 0u;
	dsvDesc.Texture2D.MipSlice = 0u;

	pDevice->CreateDepthStencilView(pDepthStencil.Get(), &dsvDesc, &pDSView);
	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDSView.Get());


	// Configure Viewport
	D3D11_VIEWPORT vp;
	vp.Width = (float)width;
	vp.Height = (float)height;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1u, &vp);


	// Setup imgui
	ImGui_ImplDX11_Init(pDevice.Get(), pContext.Get());


	return true;
}

void Graphics::EndFrame()
{
	pSwap->Present(1u, 0u);
}

void Graphics::ClearBuffer(float r, float g, float b, float a)
{
	const float color[] = { r, g, b, a };
	pContext->ClearRenderTargetView(pTarget.Get(), color);
	pContext->ClearDepthStencilView(pDSView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);

}

void Graphics::DrawIndexed(UINT count)
{
	pContext->DrawIndexed(count, 0u, 0u);
}

void Graphics::SetProjection(DirectX::XMMATRIX projection)
{
	mProjection = projection;
}

DirectX::XMMATRIX Graphics::GetProjection() const
{
	return mProjection;
}

void Graphics::SetCamera(DirectX::XMMATRIX camera)
{
	mCamera = camera;
}

DirectX::XMMATRIX Graphics::GetCamera() const
{
	return mCamera;
}
