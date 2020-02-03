#pragma once

class Application
{
public:
	Application(const std::string& name, unsigned int width, unsigned int height);
	~Application();

	void Start(GameScreen* s);

	UINT GetFramesPerSecond();

	Application& Get() { return *sInstance; }
private:
	void Run();
	void Init();

	void ImGuiInit();
	void ImGuiDestroy();
	void ImGuiBeginRender();
	void ImGuiEndRender();

	void RenderDebugInfos();
private:
	std::string fName;
	unsigned int fWidth;
	unsigned int fHeight;

	float fDeltaTime;
	UINT fFrameCounter;

	bool fRunning;
	GameScreen* fpCurrentScreen;

	Window* fpWindow;
	static Application* sInstance;
};