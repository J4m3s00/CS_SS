#include <prefix.h>

/////////////////////////D3D11_CREATE_DEVICE_DEBUG//////////////////////////////////////////////////////////////////////////
/////////////////////////D3D11_CREATE_DEVICE_DEBUG//////////////////////////////////////////////////////////////////////////
/////////////////////////D3D11_CREATE_DEVICE_DEBUG//////////////////////////////////////////////////////////////////////////
/////////////////////////D3D11_CREATE_DEVICE_DEBUG//////////////////////////////////////////////////////////////////////////
/////////////////////////D3D11_CREATE_DEVICE_DEBUG//////////////////////////////////////////////////////////////////////////
/////////////////////////D3D11_CREATE_DEVICE_DEBUG//////////////////////////////////////////////////////////////////////////
/////////////////////////D3D11_CREATE_DEVICE_DEBUG//////////////////////////////////////////////////////////////////////////

DXContext DXContext::sInstance;

DXContext::DXContext()
{

}

DXContext::~DXContext()
{
	if (fpSwapChain) fpSwapChain->Release();
	if (fpDevice) fpDevice->Release();
	if (fpDeviceContext) fpDeviceContext->Release();
	if (fpBackBuffer) fpBackBuffer->Release();
	if (fpSampler) fpSampler->Release();
}

void DXContext::Init(const Window& wnd)
{
	//Swap chain
	///////////////////////////////////////////////////////////////////////
	DXGI_SWAP_CHAIN_DESC scd = {};

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = wnd.GetHandle();
	scd.SampleDesc.Count = 1;
	scd.Windowed = TRUE;

	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&sInstance.fpSwapChain,
		&sInstance.fpDevice,
		NULL,
		&sInstance.fpDeviceContext);


	

	//Render Target
	///////////////////////////////////////////////////////////////////////
	ID3D11Texture2D* pBackBuffer;
	sInstance.fpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);


	sInstance.fpDevice->CreateRenderTargetView(pBackBuffer, NULL, &sInstance.fpBackBuffer);

	//Z-Bufer
	///////////////////////////////////////////////////////////////////////

	ID3D11Texture2D* pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = wnd.GetWidth();
	descDepth.Height = wnd.GetHeight();
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_R32_TYPELESS;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	sInstance.fpDevice->CreateTexture2D(&descDepth, 0, &pDepthStencil);



	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;


	ID3D11DepthStencilState* pDSState;
	sInstance.fpDevice->CreateDepthStencilState(&dsDesc, &pDSState);

	sInstance.fpDeviceContext->OMSetDepthStencilState(pDSState, 1u);

	

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;


	sInstance.fpDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &sInstance.fpDSView);


	//Set Viewport 
	///////////////////////////////////////////////////////////////////////
	D3D11_VIEWPORT viewport = {};

	viewport.TopLeftX = 0; 
	viewport.TopLeftY = 0;
	viewport.Width = (FLOAT) wnd.GetWidth();
	viewport.Height = (FLOAT) wnd.GetHeight();
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	sInstance.fpDeviceContext->RSSetViewports(1, &viewport);

	//Default sampler
	///////////////////////////////////////////////////////////////////////
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	sInstance.fpDevice->CreateSamplerState(&samplerDesc, &sInstance.fpSampler);
}

void DXContext::Draw(UINT vertexCount, UINT startOffset, D3D11_PRIMITIVE_TOPOLOGY topology)
{
	sInstance.fpDeviceContext->OMSetRenderTargets(1, &fpBackBuffer, fpDSView);
	fpDeviceContext->PSSetSamplers(0, 1, &fpSampler);
	fpDeviceContext->IASetPrimitiveTopology(topology);

	fpDeviceContext->Draw(vertexCount, startOffset);
}

void DXContext::DrawIndexed(UINT indexCount, UINT startOffset, D3D11_PRIMITIVE_TOPOLOGY topology)
{
	sInstance.fpDeviceContext->OMSetRenderTargets(1, &fpBackBuffer, fpDSView);
	fpDeviceContext->PSSetSamplers(0, 1, &fpSampler);
	fpDeviceContext->IASetPrimitiveTopology(topology);

	fpDeviceContext->DrawIndexed(indexCount, startOffset, 0);
}

void DXContext::Clear(const D3DXCOLOR& color)
{
	fpDeviceContext->ClearRenderTargetView(fpBackBuffer, color);
	fpDeviceContext->ClearDepthStencilView(fpDSView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DXContext::Present()
{
	fpSwapChain->Present(0, 0);
}