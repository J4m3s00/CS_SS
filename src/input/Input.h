#pragma once

typedef std::function<void(int, bool, bool)> FnKeyCallback;

class Keyboard
{
	friend class Window;
public:
	Keyboard();

	static bool IsKeyDown(int key);
	static bool IsKeyPressed(int key);
private:
	void SetKeyState(int flags, int key, unsigned int message);
	void AddKeyCallack(FnKeyCallback callback);
private:
	static constexpr int nKeyCount = 256;
	static bool sKeyStates[nKeyCount];
	std::vector<FnKeyCallback> fCallbacks;
};

class Mouse
{

};