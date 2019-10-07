#include "prefix.h"
#include <iostream>

int CALLBACK WinMain(_In_ HINSTANCE hInstace, _In_opt_ HINSTANCE hPrevInstace, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Window* window = new Window(1270, 720, "Hello World");

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

	return msg.wParam;
}