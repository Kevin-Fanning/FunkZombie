#include "stdafx.h"

#include "GameObject.h"

GameObject::GameObject(unsigned int ID)
{
	m_ID = ID;
}

GameObject::~GameObject()
{

}

void GameObject::Init()
{

}

void GameObject::Update(int delta)
{

}

void GameObject::Destroy()
{

}

void GameObject::addComponent(std::shared_ptr<GameObjectComponent> component)
{
	m_pComponents.push_back(component);
}