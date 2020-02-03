#include "prefix.h"

class TestApp : public Application
{
public:
	TestApp()
		: Application("HEllo World", 1270, 720)
	{

	}
};


int WinMain(HINSTANCE hInsatance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) 
{
	TestApp app;
	GameScreen screen("Hello Screen");
	app.Start(&screen);

}