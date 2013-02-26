#pragma once

#include <list>
#include <memory>
#include <glm/glm.hpp>

class GameObject;

class IComponent
{
public:
	virtual ~IComponent(){ m_owner.reset();}

	virtual void VInit() = 0;

	virtual void VUpdate(int delta) {}

	virtual void VDraw(){}

	void setOwner(std::shared_ptr<GameObject> in);
	
protected:
	std::shared_ptr<GameObject> m_owner;
};

typedef std::list<std::shared_ptr<IComponent>> ComponentPList;

class GameObject
{
public:
	GameObject();
	~GameObject();
	void addComponent(std::shared_ptr<IComponent>, std::shared_ptr<GameObject>);

	void Destroy();
	void Update(int delta);

	void Draw();

	glm::vec3 getPosition() const {return m_position;}
	glm::vec3 getRotation() const {return m_rotation;}
	glm::vec3 getScale() const {return m_scale;}

protected:
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	glm::vec3 m_position;
	ComponentPList m_components;
	
	
};


