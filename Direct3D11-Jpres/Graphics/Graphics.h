#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>

class Graphics
{
	friend class Bindable;
public:
	bool Initialize(HWND hWnd);
	void EndFrame();
	void ClearBuffer(float r, float g, float b, float a);
	void DrawIndexed(UINT count);

	void SetProjection(DirectX::XMMATRIX projection);
	DirectX::XMMATRIX GetProjection() const;


private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSView;

	DirectX::XMMATRIX mProjection;
};