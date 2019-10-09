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

	Material mat("Basic");


	Vertex vertices[] =
	{
		{-0.5f, -0.5f, 1.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
		{ 0.0f,  0.5f, 1.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
		{ 0.5f, -0.5f, 1.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
	};

	DXBuffer vertexBuffer(BUFFER_TYPE_VERTEX_BUFFER, vertices, sizeof(Vertex), sizeof(vertices) / sizeof(Vertex));


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

			vertexBuffer.Bind();


			//Mesh

			///////////////////////////////////////////////////////////////

			DXContext::sInstance.DrawInstanced(3);

			DXContext::sInstance.Present();
		}
	}

	return msg.wParam;
}