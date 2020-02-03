#pragma once
class Window
{
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass();
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* sWndClassName = "CSSS Window";
		static WindowClass sWndClass;
		HINSTANCE fHInstance;
	};

public:
	Window(unsigned int width, unsigned int height, const std::string& title);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	HWND GetHandle() const { return fHwnd; }
	int GetWidth() const { return fWidth; }
	int GetHeight() const { return fHeight; }

	void AddKeyCallback(FnKeyCallback callback);
	void AddMouseCallback(FnMouseCallback callback);
	void AddMouseMoveCallback(FnMouseMoveCallback callback);
private:
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	int fWidth;
	int fHeight;
	HWND fHwnd;
	Keyboard fKeyboard;
	Mouse fMouse;
public:
	static Window* sInstance;
};

