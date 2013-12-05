#pragma once

#include "GameObjectComponent.h"
#include <list>

class GameObject 
{
public:
	explicit GameObject(unsigned int ID);
	~GameObject();

	void Init();
	void Update(int delta);
	void Destroy();

	template <class T>
	std::weak_ptr<T> getComponent (char* component)
	{
		for (std::iterator<GameObjectComponent> it = m_pComponents.begin(); it != m_pComponents.end(); it++)
		{
			if (it->VGetName() == component)
			{
				std::shared_ptr<GameObjectComponent> pBase = *it;
				std::shared_ptr<T> pSub = std::static_pointer_cast<T>(pBase);
				std::weak_ptr<T> pWeak(pSub);
				return pWeak;
			}
		}
		return std::weak_ptr<T>();
	}

protected:

	void addComponent(std::shared_ptr<GameObjectComponent> component);

	unsigned int m_ID;

	std::list<std::shared_ptr<GameObjectComponent>> m_pComponents;
};