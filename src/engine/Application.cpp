#include "prefix.h"

Application::Application(const std::string& name, unsigned int width, unsigned int height)
	: fpCurrentScreen(nullptr), fpWindow(nullptr), fRunning(false), fName(name), fWidth(width), fHeight(height)
{

}

Application::~Application()
{

}

void Application::Start(GameScreen* screen)
{
	if (fpCurrentScreen)
		fpCurrentScreen->Stop();
	
	fpCurrentScreen = screen;

	if (!fRunning)
		Run();
}

void Application::Init()
{
	fpWindow = new Window(fWidth, fHeight, fName);

	fRunning = true;

	if (fpCurrentScreen)
		fpCurrentScreen->Load();
}

void Application::Run()
{
	Init();

	Timer t;
	MSG msg;
	while (fRunning)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
			if (msg.message == WM_QUIT)
			{
				fRunning = false;
				break;
			}
		}
		else
		{
			static float delta = 0.0f;
			delta = t.Reset();

			DXContext::sInstance.Clear();

			if (fpCurrentScreen)
				fpCurrentScreen->Update(delta);

			DXContext::sInstance.Present();
		}
	}

	if (fpCurrentScreen)
		fpCurrentScreen->Unload();
}