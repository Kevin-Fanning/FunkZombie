#pragma once

#include <glm/glm.hpp>
class Vertex
{
public:
	Vertex(glm::vec3 pos, glm::vec2 uv)
		: m_pos(pos), m_uv(uv)
	{
		
	}
protected:
	glm::vec3 m_pos;
	glm::vec2 m_uv;
};

