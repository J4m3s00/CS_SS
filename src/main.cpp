#include "prefix.h"
#include <iostream>

int CALLBACK WinMain(_In_ HINSTANCE hInstace, _In_opt_ HINSTANCE hPrevInstace, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Window* window = new Window(1270, 720, "Hello World");

	//Init Shader
	ID3D10Blob* VS, * PS;
	D3DX11CompileFromFile("src/shader/Basic.hlsl", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
	D3DX11CompileFromFile("src/shader/Basic.hlsl", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

	ID3D11VertexShader* pVS; 
	ID3D11PixelShader* pPS;

	auto device = DXContext::sInstance.GetDevice();
	device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	auto devcon = DXContext::sInstance.GetDeviceContext();
	devcon->VSSetShader(pVS, 0, 0);
	devcon->PSSetShader(pPS, 0, 0);

	MSG msg;
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			DXContext::sInstance.Clear();

			DXContext::sInstance.Present();
		}
	}

	pVS->Release();
	pPS->Release();

	return msg.wParam;
}