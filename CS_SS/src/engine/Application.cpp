#include "prefix.h"

#define SHOW_DEBUG_INFO

Application* Application::sInstance = nullptr;

Application::Application(const std::string& name, unsigned int width, unsigned int height)
	: fpCurrentScreen(nullptr), fpWindow(nullptr), fRunning(false), fName(name), fWidth(width), fHeight(height), fDeltaTime(0.0f)
{
	sInstance = this;
}

Application::~Application()
{

}

void Application::Start(GameScreen* screen)
{
	if (fpCurrentScreen)
		fpCurrentScreen->Stop();
	
	fpCurrentScreen = screen;

	fpCurrentScreen->Start();

	if (!fRunning)
		Run();
}

void Application::Init()
{
	if (!fpWindow)
		fpWindow = new Window(fWidth, fHeight, fName);

	ImGuiInit();

	fRunning = true;

	if (fpCurrentScreen)
		fpCurrentScreen->Load();
}

void Application::Run()
{
	Init();

	Timer t;
	Timer fpsUpdates;
	MSG msg;
	static UINT counter = 0;
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
			fDeltaTime = t.Reset();
			counter++;

			if (fpsUpdates.GetDuration() >= 1.0f)
			{
				fFrameCounter = counter;
				counter = 0;
				fpsUpdates.Reset();
			}

			DXContext::sInstance.Clear();

			if (fpCurrentScreen)
				fpCurrentScreen->Update(fDeltaTime);

			ImGuiBeginRender();
			RenderDebugInfos();
			if (fpCurrentScreen)
				fpCurrentScreen->RenderImGui();
			ImGuiEndRender();

			DXContext::sInstance.Present();
		}
	}

	if (fpCurrentScreen)
		fpCurrentScreen->Unload();

	ImGuiDestroy();
}

void Application::ImGuiInit()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(fpWindow->GetHandle());
	ImGui_ImplDX11_Init(DXContext::sInstance.GetDevice(), DXContext::sInstance.GetDeviceContext());
}

void Application::ImGuiDestroy()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Application::ImGuiBeginRender()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Application::ImGuiEndRender()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
}

UINT Application::GetFramesPerSecond()
{
	return fFrameCounter;
}

void Application::RenderDebugInfos()
{
#if  defined (_DEBUG) || defined(SHOW_DEBUG_INFO)
	
	ImGui::Begin("DebugInfos##Application_Debug_Infos");
	ImGui::Text("Delta Time: %f", fDeltaTime);
	ImGui::Text("Frames Per Second: %d", GetFramesPerSecond());
	ImGui::End();
#endif // _DEBUG

}