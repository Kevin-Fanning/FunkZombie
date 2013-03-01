#pragma once
#include <glm/glm.hpp>
struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 uv;

	Vertex() : position(0.f), color(1.f), uv(0.f){}
	Vertex(glm::vec3 pos, glm::vec3 col, glm::vec2 texCoord)
		: position(pos), color(col), uv(texCoord) {}
};

