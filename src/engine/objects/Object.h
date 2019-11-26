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
	GameObject(const std::string& name, const DirectX::XMFLOAT3& position = { 0.0f, 0.0f, 0.0f }, const DirectX::XMFLOAT3& rotation = {0.0f, 0.0f, 0.0f});

	virtual void OnLoad();
	virtual void OnUnload();
	virtual void OnUpdate(float delta);
	virtual void OnStart();
	virtual void OnStop();
protected:
	DirectX::XMFLOAT3 fPosition;
	DirectX::XMFLOAT3 fRotation;
};