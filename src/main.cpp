#include "prefix.h"
#include <iostream>


int CALLBACK WinMain(_In_ HINSTANCE hInstace, _In_opt_ HINSTANCE hPrevInstace, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Window* window = new Window(1270, 720, "Hello World");

	MaterialBasic mat;
	MaterialBasic::ConstantBuffer* pMaterialBuffer = mat.GetConstantBuffer();
	pMaterialBuffer->fModelMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationY(0.0f) * DirectX::XMMatrixTranslation(0, 0, 0));

	std::vector<Mesh::Vertex> vertices =
	{
		{-0.5f, -0.5f, 0.5f, 1, 1},		//0
		{-0.5f,  0.5f, 0.5f, 1, 0},		//1
		{ 0.5f,  0.5f, 0.5f, 0, 0},		//2
		{ 0.5f, -0.5f, 0.5f, 0, 1},		//3
										//
										//
		{-0.5f, -0.5f, -0.5f, 1, 1},	//4
		{-0.5f,  0.5f, -0.5f, 1, 0},	//5
		{ 0.5f,  0.5f, -0.5f, 0, 0},	//6
		{ 0.5f, -0.5f, -0.5f, 0, 1},	//7
										//
		{0.5f, -0.5f, -0.5f, 1, 1},		//8
		{0.5f, -0.5f,  0.5f, 1, 0},		//9
		{0.5f,  0.5f,  0.5f, 0, 0},		//10
		{0.5f,  0.5f, -0.5f, 0, 1},		//11
										//
		{-0.5f, -0.5f, -0.5f, 1, 1},	//12
		{-0.5f, -0.5f,  0.5f, 1, 0},	//13
		{-0.5f,  0.5f,  0.5f, 0, 0},	//14
		{-0.5f,  0.5f, -0.5f, 0, 1},	//15
										//
		{-0.5f, 0.5f, -0.5f, 1, 1},		//16
		{-0.5f, 0.5f,  0.5f, 1, 0},		//17
		{ 0.5f, 0.5f,  0.5f, 0, 0},		//18
		{ 0.5f, 0.5f, -0.5f, 0, 1},		//19
										//
		{-0.5f, -0.5f, -0.5f, 1, 1},	//20
		{-0.5f, -0.5f,  0.5f, 1, 0},	//21
		{ 0.5f, -0.5f,  0.5f, 0, 0},	//22
		{ 0.5f, -0.5f, -0.5f, 0, 1},	//23
	};

	std::vector<USHORT> indices =
	{
		0, 2, 1,
		2, 0, 3,

		4, 5, 6,
		6, 7, 4,

		8, 10, 9,
		10, 8, 11,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 22, 21,
		23, 22, 20,
	};

	Mesh m(vertices, indices);

	MSG msg;

	Timer t;

	float x = 0;

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
			static float delta = 0.0f;
			delta = t.Reset();

			//x = sinf(delta / 100) * 10000;
			x += delta / 1;

			pMaterialBuffer->fModelMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationY(x) * DirectX::XMMatrixTranslation(0, 0, 2));

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