#include "prefix.h"
#include <iostream>

struct Vertex
{
	float x;
	float y; 
	float z;
	D3DXCOLOR Color;
};

int CALLBACK WinMain(_In_ HINSTANCE hInstace, _In_opt_ HINSTANCE hPrevInstace, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Window* window = new Window(1270, 720, "Hello World");

	//Init Shader
	/*ID3D10Blob* VS, * PS;
	D3DX11CompileFromFile("src/shader/Basic.hlsl", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
	D3DX11CompileFromFile("src/shader/Basic.hlsl", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

	//Global
	ID3D11VertexShader* pVS; 
	ID3D11PixelShader* pPS;

	//Initilization

	device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);
	*/
	auto device = DXContext::sInstance.GetDevice();
	auto devcon = DXContext::sInstance.GetDeviceContext();

	Shader<ID3D11VertexShader> vertexShader("src/shader/Basic.hlsl");
	Shader<ID3D11PixelShader> pixelShader("src/shader/Basic.hlsl");


	//Input Layout
	//Global
	ID3D11InputLayout* pLayout;

	//Initialization
	D3D11_INPUT_ELEMENT_DESC inputDescription[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	device->CreateInputLayout(inputDescription, 2, vertexShader.GetBlob()->GetBufferPointer(), vertexShader.GetBlob()->GetBufferSize(), &pLayout);
	//Bind method


	//Init VBO
	Vertex vertices[] =
	{
		{-0.5f, -0.5f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},
		{ 0.0f,  0.5f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},
		{ 0.5f, -0.5f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)},
	};

	//Global
	ID3D11Buffer* pVBuffer;

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(vertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA ms;
	ms.pSysMem = vertices;
	device->CreateBuffer(&bd, &ms, &pVBuffer);


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


			//Bind method
			///////////////////////////////////////////////////////////////
			//Material
			vertexShader.Bind();
			pixelShader.Bind();

			devcon->IASetInputLayout(pLayout); 



			//Mesh
			UINT stride = sizeof(Vertex);
			UINT offset = 0;
			devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

			///////////////////////////////////////////////////////////////

			DXContext::sInstance.DrawInstanced(3);

			DXContext::sInstance.Present();
		}
	}

	return msg.wParam;
}