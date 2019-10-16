#include <prefix.h>

bool Keyboard::sKeyStates[nKeyCount];

Keyboard::Keyboard()
	: fCallbacks()
{
	
}

bool Keyboard::IsKeyDown(int key)
{
	if (key < 0 || key > nKeyCount) { return false; }
	return sKeyStates[key];
}

bool Keyboard::IsKeyPressed(int key)
{
	if (key < 0 || key > nKeyCount) { return false; }
	return sKeyStates[key];
}

void Keyboard::SetKeyState(int flags, int key, unsigned int message)
{
	bool pressed = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;
	sKeyStates[key] = pressed;

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