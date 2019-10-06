#include "prefix.h"
#include <iostream>

int CALLBACK WinMain(_In_ HINSTANCE hInstace, _In_opt_ HINSTANCE hPrevInstace, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Window* window = new Window(1270, 720, "Hello World");

	window->Create(hInstace);

	MSG msg;
	BOOL gResult;
	while (( gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	};

	return msg.wParam;
}