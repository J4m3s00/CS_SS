#include "prefix.h"

Object::Object(const std::string& name)
	: fName(name)
{}

GameObject::GameObject(const std::string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: Object(name), fPosition(position), fRotation(rotation), fScale(scale)
{

}

void GameObject::OnLoad()
{

}

void GameObject::OnUnload()
{

}

void GameObject::OnStart() 
{

}

void GameObject::OnStop()
{

}

void GameObject::OnUpdate(float delta)
{

}