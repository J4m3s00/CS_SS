#include <prefix.h>


Keyboard::Keyboard()
	: fCallbacks()
{
	
}
void Keyboard::SetKeyState(int flags, int key, unsigned int message)
{
	bool pressed = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;
	bool repeat = (flags >> 30) & 1;

	//Maybe implement modifier
	for (FnKeyCallback callback : fCallbacks)
	{
		callback(key, pressed, repeat);
	}
}

void Keyboard::AddKeyCallack(FnKeyCallback callback)
{
	fCallbacks.push_back(callback);
}

void Mouse::SetMouseState(UINT msg, short xPos, short yPos)
{
	fXPos = xPos;
	fYPos = yPos;
	unsigned char button = 0;
	bool down = false;

	switch (msg)
	{
	case WM_LBUTTONDOWN:
		down = true;
		button = MouseButtons::LEFT;
		break;
	case WM_LBUTTONUP:
		down = false;
		button = MouseButtons::LEFT;
		break;
	case WM_RBUTTONDOWN:
		down = true;
		button = MouseButtons::RIGHT;
		break;
	case WM_RBUTTONUP:
		down = false;
		button = MouseButtons::RIGHT;
		break;
	case WM_MBUTTONDOWN:
		down = true;
		button = MouseButtons::MIDDLE;
		break;
	case WM_MBUTTONUP:
		down = false;
		button = MouseButtons::MIDDLE;
		break;
	}

	for (FnMouseCallback callback : fMouseCallbacks)
	{
		callback(xPos, yPos, button, down);
	}
}

void Mouse::SetMouseMove(UINT msg, WPARAM wParam, short xPos, short yPos)
{
	short deltaX = xPos - fXPos;
	short deltaY = yPos - fYPos;

	fXPos = xPos;
	fYPos = yPos;

	bool left = (wParam & MK_LBUTTON);
	bool right = (wParam & MK_RBUTTON);
	bool middle = (wParam & MK_MBUTTON);

	unsigned char buttons = (left ? MouseButtons::LEFT : 0) | (right ? MouseButtons::RIGHT : 0) | (middle ? MouseButtons::MIDDLE : 0);

	for (FnMouseMoveCallback callback : fMouseMoveCallbacks)
	{
		callback(xPos, yPos, buttons, deltaX, deltaY);
	}
}

void Mouse::AddMouseCallback(FnMouseCallback callback)
{
	fMouseCallbacks.push_back(callback);
}

void Mouse::AddMouseMoveCallback(FnMouseMoveCallback callback)
{
	fMouseMoveCallbacks.push_back(callback);
}