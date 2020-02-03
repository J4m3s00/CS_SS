#include "prefix.h"

class TestScreen : public GameScreen
{
public:
	TestScreen()
		: GameScreen("Hello Game")
	{

	}
};

int WinMain(HINSTANCE hInstance, HINSTANCE hPRevInstance, PSTR cmdLine, int cmdShow)
{
	Application app("Test App", 1270, 720);
	TestScreen s;

	app.Start(&s);

	return 0;
}