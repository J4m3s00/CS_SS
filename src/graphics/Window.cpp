#include <prefix.h>

Window::WindowClass Window::WindowClass::sWndClass;
Window* Window::sInstance = nullptr;

Window::WindowClass::WindowClass()
	: fHInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = Window::HandleMsgThunk;
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
	sInstance = this;
	RECT wr;
	wr.left = 0;
	wr.right = width;
	wr.top = 0;
	wr.bottom = height;
	AdjustWindowRectEx(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE, 0);
	

	fHwnd = CreateWindowEx(0, WindowClass::GetName(), "", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, WindowClass::GetInstance(), nullptr);

	DXContext::Init(*this);

	ShowWindow(fHwnd, SW_SHOW);
}

Window::~Window()
{
	DestroyWindow(fHwnd);
}


LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return sInstance->HandleMsg(hWnd, msg, wParam, lParam);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYUP:
		fKeyboard.SetKeyState(lParam, wParam, msg);
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		fMouse.SetMouseState(msg, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_MOUSEMOVE:
		fMouse.SetMouseMove(msg, wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Window::AddKeyCallback(FnKeyCallback callback)
{
	fKeyboard.AddKeyCallack(callback);
}

void Window::AddMouseMoveCallback(FnMouseMoveCallback callback)
{
	fMouse.AddMouseMoveCallback(callback);
}

void Window::AddMouseCallback(FnMouseCallback callback)
{
	fMouse.AddMouseCallback(callback);
}