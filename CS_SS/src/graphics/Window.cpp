#include "../prefix.h"

const auto CLASS_NAME = "CSSS Window Class";
static Window* sInstance;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Window(unsigned int width, unsigned int height, const std::string& title)
	: fWidth(width), fHeight(height), fTitle(title)
{
	sInstance = this;
	
}

Window::~Window()
{

}

bool Window::Create(HINSTANCE hInstance)
{
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowEx(0, CLASS_NAME, fTitle.c_str(), WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, fWidth, fHeight, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd) return false;
	ShowWindow(hWnd, SW_SHOW);

	return true;


}