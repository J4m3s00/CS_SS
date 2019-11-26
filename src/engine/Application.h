#pragma once

class Application
{
public:
	Application(const std::string& name, unsigned int width, unsigned int height);
	~Application();

	void Start(GameScreen* s);
private:
	void Run();
	void Init();
private:
	std::string fName;
	unsigned int fWidth;
	unsigned int fHeight;


	bool fRunning;
	GameScreen* fpCurrentScreen;

	Window* fpWindow;
};