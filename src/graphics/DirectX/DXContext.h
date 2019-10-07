#pragma once

class DXContext
{
public:
	DXContext();
	~DXContext();
	DXContext(const DXContext&) = delete;
	DXContext& operator=(const DXContext&) = delete;

	void Clear(const D3DXCOLOR& color = D3DXCOLOR(0.5f, 0.7f, 0.74f, 1.0f));
	void Present();

	static void Init(const Window& wnd);
private:
	IDXGISwapChain* fpSwapChain = nullptr;
	ID3D11Device* fpDevice = nullptr;
	ID3D11DeviceContext* fpDeviceContext = nullptr;
	ID3D11RenderTargetView* fpBackBuffer = nullptr;
public:
	static DXContext sInstance;
};