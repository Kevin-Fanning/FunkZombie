#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.h"
#include "ShaderProgram.h"
#include "Transform.h"

class Renderer : public IComponent
{
public:
	Renderer(void);

	void VInit();
	void VUpdate(int delta);
	void VDraw();

protected:
	ShaderProgram shaderProgram;
	glm::vec4 color;
	glm::mat4 worldTransform;

	static glm::vec3 vertices[];
};

