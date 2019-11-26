#include "prefix.h"

GameScreen::GameScreen(const std::string& name)
	: fName(name)
{

}

GameScreen::~GameScreen()
{

}

void GameScreen::AddGameObject(GameObject* gameObject)
{
	fGameObjectList.push_back(gameObject);
}

void GameScreen::RemoveGameObject(GameObject* gameObject, bool deleteAfter)
{
	std::vector<GameObject*>::iterator it = std::find(fGameObjectList.begin(), fGameObjectList.end(), gameObject);
	if (it != fGameObjectList.end())
	{
		if (deleteAfter)
			delete* (it);
		fGameObjectList.erase(it);
	}
}

void GameScreen::Load() 
{
	OnLoad();
	for (GameObject* go : fGameObjectList)
		go->OnLoad();

}

void GameScreen::Unload()
{
	OnUnload();
	for (GameObject* go : fGameObjectList)
		go->OnUnload();
}

void GameScreen::Start()
{
	OnStart();
	for (GameObject* go : fGameObjectList)
		go->OnStart();
}

void GameScreen::Stop()
{
	OnStop(); 
	for (GameObject* go : fGameObjectList)
		go->OnStop();
}

void GameScreen::Update(float delta)
{
	OnUpdate(delta);
	for (GameObject* go : fGameObjectList)
		go->OnUpdate(delta);
}
void GameScreen::RenderImGui()
{
	OnRenderImGui();
	for (GameObject* go : fGameObjectList)
		go->OnRenderImGui();
}