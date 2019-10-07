#include "../prefix.h"

Window::WindowClass Window::WindowClass::sWndClass;

Window::WindowClass::WindowClass()
	: fHInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = Window::HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(sWndClassName, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
	return sWndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return sWndClass.fHInstance;
}

Window::Window(unsigned int width, unsigned int height, const std::string& title)
	: fWidth(width), fHeight(height)
{
	RECT wr;
	wr.left = 0;
	wr.right = width;
	wr.top = 0;
	wr.left = height;
	AdjustWindowRectEx(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE, 0);

	fHwnd = CreateWindowEx(0, WindowClass::GetName(), "", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, fWidth, fHeight, nullptr, nullptr, WindowClass::GetInstance(), nullptr);

	ShowWindow(fHwnd, SW_SHOW);
}

Window::~Window()
{
	DestroyWindow(fHwnd);
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));

		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}