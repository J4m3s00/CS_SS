#include "prefix.h"
#include <iostream>


int CALLBACK WinMain(_In_ HINSTANCE hInstace, _In_opt_ HINSTANCE hPrevInstace, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Window* window = new Window(1270, 720, "Hello World");

	MaterialBasic mat;


	std::vector<Mesh::Vertex> vertices =
	{
		{-0.5f, -0.5f, 1.0f, 1, 1},
		{-0.5f,  0.5f, 1.0f, 1, 0},
		{ 0.5f,  0.5f, 1.0f, 0, 0},
		{ 0.5f, -0.5f, 1.0f, 0, 1},
	};

	std::vector<USHORT> indices =
	{
		0, 1, 2,
		2, 3, 0,
	};

	Mesh m(vertices, indices);

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

			m.Draw();

			DXContext::sInstance.Present();
		}
	}

	return msg.wParam;
}