#pragma once

#include <memory>

class GameObject;

class GameObjectComponent
{
public:
	
	~GameObjectComponent()
	{
		m_pOwner.reset();
	}

	void Init() {}
	void Update(int delta) {}

	virtual char* VGetName() = 0;
protected:
	std::shared_ptr<GameObject> m_pOwner;

	void setOwner(std::shared_ptr<GameObject> parent)
	{
		m_pOwner = parent;
	}
};