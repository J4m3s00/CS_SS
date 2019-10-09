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

	MaterialBasic mat;


	Vertex vertices[] =
	{
		{-0.5f, -0.5f, 1.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
		{-0.5f,  0.5f, 1.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
		{ 0.5f,  0.5f, 1.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
		{ 0.5f, -0.5f, 1.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
	};

	UINT indices[] =
	{
		0, 1, 2,
		2, 3, 0,
	};

	DXBuffer vertexBuffer(BUFFER_TYPE_VERTEX_BUFFER, vertices, sizeof(Vertex), sizeof(vertices) / sizeof(Vertex));
	DXBuffer indexBuffer(BUFFER_TYPE_INDEX_BUFFER, indices, sizeof(UINT), sizeof(indices) / sizeof(UINT));


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
			mat.Bind();

			indexBuffer.Bind();
			vertexBuffer.Bind();

			//Mesh

			///////////////////////////////////////////////////////////////

			DXContext::sInstance.DrawIndexed(6);

			DXContext::sInstance.Present();
		}
	}

	return msg.wParam;
}