#pragma once

class Object
{
public:
	Object(const std::string& name);
private:
	std::string fName;
};

class GameObject : public Object
{
public:
	GameObject(const std::string& name, const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, const glm::vec3& rotation = {0.0f, 0.0f, 0.0f});

	virtual void OnLoad();
	virtual void OnUnload();
	virtual void OnUpdate(float delta);
	virtual void OnStart();
	virtual void OnStop();
protected:
	glm::vec3 fPosition;
	glm::vec3 fRotation;
};