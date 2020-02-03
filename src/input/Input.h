#pragma once

typedef std::function<void(int, bool, bool)> FnKeyCallback;
typedef std::function<void(short, short, unsigned char, bool)> FnMouseCallback;
typedef std::function<void(short, short, unsigned char, short, short)> FnMouseMoveCallback;

enum MouseButtons : unsigned char
{
	LEFT = (1 << 0),
	RIGHT = (1 << 1),
	MIDDLE = (1 << 2)
};

class Keyboard
{
	friend class Window;
public:
	Keyboard();

private:
	void SetKeyState(int flags, int key, unsigned int message);
	void AddKeyCallack(FnKeyCallback callback);
private:
	std::vector<FnKeyCallback> fCallbacks;
};

class Mouse
{
	friend class Window;
public:
private:
	void SetMouseState(UINT message, short xPos, short yPos);
	void SetMouseMove(UINT msg, WPARAM wParam, short xPos, short yPos);
	void AddMouseCallback(FnMouseCallback callback);
	void AddMouseMoveCallback(FnMouseMoveCallback callback);
private:
	short fXPos;
	short fYPos;
	std::vector<FnMouseCallback> fMouseCallbacks;
	std::vector<FnMouseMoveCallback> fMouseMoveCallbacks;
};