#pragma once
#include <glm/glm.hpp>
#include "GameObject.h"
class Transform : public IComponent
{
public:
	Transform(void)
	{
		scale = glm::vec3(0.f, 0.f, 0.f);
		rotation = glm::vec3(0.f, 0.f, 0.f);
		position = glm::vec3(0.f, 0.f, 0.f);
	}

	void VInit(){}
	void VUpdate(int delta){}
	void VDraw(){}

	glm::vec3 getPosition() const {return position;}
	glm::vec3 getRotation() const {return rotation;}
	glm::vec3 getScale() const {return scale;}
protected:
	glm::vec3 scale;
	glm::vec3 rotation;
	glm::vec3 position;
};

