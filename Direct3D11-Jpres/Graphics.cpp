#include "Graphics.h"
#include "ErrorLogger.h"

#include <math.h>
#include <vector>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "Bindable.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Topology.h"
#include "InputLayout.h"

#include <memory>

using namespace Microsoft::WRL;

bool Graphics::Initialize(HWND hWnd)
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
	tDesc.Width = 800;
	tDesc.Height = 600;
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
	vp.Width = 800;
	vp.Height = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1u, &vp);


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

void Graphics::DrawTriangle(float angle)
{

	struct Vertex
	{
		float x, y, z;
		unsigned char r, g, b, a;
	};

	Vertex vertices[] =
	{
		{ -1.0f,-1.0f,-1.0f, 255, 0,0,255},
		{ 1.0f,-1.0f,-1.0f, 0,255,0,255},
		{ -1.0f,1.0f,-1.0f, 0,0,255,255},
		{ 1.0f,1.0f,-1.0f, 255, 255, 0,255},
		{ -1.0f,-1.0f,1.0f, 255,0,255,255},
		{ 1.0f,-1.0f,1.0f,0,255,255,255},
		{ -1.0f,1.0f,1.0f,255,255,255,255},
		{ 1.0f,1.0f,1.0f,0,0,0,255},
	};

	const unsigned short indices[] =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	struct ConstantBuffer
	{
		DirectX::XMMATRIX transform;
	};

	const ConstantBuffer cb =
	{
		DirectX::XMMatrixTranspose(
		DirectX::XMMatrixRotationZ(angle) *
		DirectX::XMMatrixRotationX(angle) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f) *
		DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 100.0f)
		)
	};

	{
		ComPtr<ID3D11Buffer> pVertexBuffer;
		D3D11_BUFFER_DESC bd = {};
		bd.ByteWidth = sizeof(vertices);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		bd.StructureByteStride = sizeof(Vertex);

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices;

		pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer);

		const UINT stride = sizeof(Vertex);
		const UINT offset = 0u;
		pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	}

	{
		ComPtr<ID3D11Buffer> pIndexBuffer;
		D3D11_BUFFER_DESC ibd = {};
		ibd.ByteWidth = sizeof(indices);
		ibd.Usage = D3D11_USAGE_DEFAULT;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		ibd.StructureByteStride = sizeof(unsigned short);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = indices;

		pDevice->CreateBuffer(&ibd, &sd, &pIndexBuffer);
		pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

	}

	{
		ComPtr<ID3D11Buffer> pConstantBuffer;
		D3D11_BUFFER_DESC cbd = {};
		cbd.ByteWidth = sizeof(cb);
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0;
		cbd.StructureByteStride = sizeof(ConstantBuffer);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = &cb;

		pDevice->CreateBuffer(&cbd, &sd, &pConstantBuffer);
		pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}


	ComPtr<ID3DBlob> pBlob;
	{
		ComPtr<ID3D11VertexShader> pVertexShader;
		D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
		pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
		pContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	}

	{
		ComPtr<ID3D11InputLayout> pLayout;
		const D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"Color", 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pLayout);
		pContext->IASetInputLayout(pLayout.Get());
	}

	{
		ComPtr<ID3D11PixelShader> pPixelShader;
		D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
		pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
		pContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	}


	pContext->DrawIndexed((UINT)std::size(indices), 0u, 0u);

}


void Graphics::DrawTriangleNew(float angle)
{
	std::vector<std::unique_ptr<Bindable>> bindables;

	struct Vertex
	{
		float x, y, z;
		unsigned char r, g, b, a;
	};
	std::vector<Vertex> vertices =
	{
		{ -1.0f,-1.0f,-1.0f, 255, 0,0,255},
		{ 1.0f,-1.0f,-1.0f, 0,255,0,255},
		{ -1.0f,1.0f,-1.0f, 0,0,255,255},
		{ 1.0f,1.0f,-1.0f, 255, 255, 0,255},
		{ -1.0f,-1.0f,1.0f, 255,0,255,255},
		{ 1.0f,-1.0f,1.0f,0,255,255,255},
		{ -1.0f,1.0f,1.0f,255,255,255,255},
		{ 1.0f,1.0f,1.0f,0,0,0,255},
	};

	bindables.push_back(std::make_unique<VertexBuffer>(*this, vertices));
	const std::vector<unsigned short> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	auto ib = std::make_unique<IndexBuffer>(*this, indices);
	UINT indexCount = ib->GetCount();
	bindables.push_back(std::move(ib));

	DirectX::XMMATRIX transform = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixRotationZ(angle) *
		DirectX::XMMatrixRotationX(angle) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f) *
		DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 100.0f));

	bindables.push_back(std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(*this, transform));


	auto vs = std::make_unique<VertexShader>(*this, "VertexShader.cso");
	auto pvsbc = vs->GetByteCode();
	bindables.push_back(std::move(vs));

	bindables.push_back(std::make_unique<PixelShader>(*this, "PixelShader.cso"));


	std::vector<D3D11_INPUT_ELEMENT_DESC> layout =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color", 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	bindables.push_back(std::make_unique<InputLayout>(*this, layout, pvsbc));

	bindables.push_back(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));


	for (auto& b : bindables)
	{
		b->Bind(*this);
	}

	pContext->DrawIndexed(indexCount, 0u, 0u);

}