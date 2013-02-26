#include "stdafx.h"
#include "GameObject.h"
#include <iostream>

GameObject::GameObject(void)
{
	m_position = glm::vec3(0.f, 0.f, 0.f);
	m_rotation = glm::vec3(0.f, 0.f, 0.f);
	m_scale = glm::vec3(1.f, 1.f, 1.f);
}

GameObject::~GameObject()
{
	assert(m_components.empty());
}

void GameObject::Destroy()
{
	m_components.clear();
}

void GameObject::Update(int delta)
{
	for (ComponentPList::iterator i = m_components.begin(); i != m_components.end(); ++i)
	{
		(*i)->VUpdate(delta);
	}
}

void GameObject::Draw()
{
	for (ComponentPList::iterator i = m_components.begin(); i != m_components.end(); ++i)
	{
		(*i)->VDraw();
	}
}

void GameObject::addComponent(std::shared_ptr<IComponent> pComponent, std::shared_ptr<GameObject> go)
{
	pComponent->setOwner(go);
	pComponent->VInit();
	m_components.push_back(pComponent);
}

void IComponent::setOwner(std::shared_ptr<GameObject> in)
{
	m_owner = in;
}