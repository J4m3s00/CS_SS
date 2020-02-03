#pragma once

class GameScreen
{
public:
	GameScreen(const std::string& name);
	~GameScreen();

	void AddGameObject(GameObject* gameObject);
	void RemoveGameObject(GameObject* gameObject, bool deleteAfter = false);

	void Load();
	void Unload();
	void Start();
	void Stop();
	void Update(float delta);
	void RenderImGui();
protected:
	virtual void OnLoad() {}
	virtual void OnUnload() {}
	virtual void OnStart() {}
	virtual void OnStop() {}
	virtual void OnUpdate(float delta) {}
	virtual void OnRenderImGui() {}
private:
	std::string fName;
	std::vector<GameObject*> fGameObjectList;
};