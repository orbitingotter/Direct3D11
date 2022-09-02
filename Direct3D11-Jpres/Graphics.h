#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <wrl.h>

class Graphics
{
public:
	bool Initialize(HWND hWnd);
	void EndFrame();
	void ClearBuffer(float r, float g, float b, float a);

	void DrawTriangle(float angle);


private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
};