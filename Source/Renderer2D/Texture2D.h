#pragma once

#include "Resource Manager/ResourceManager.h"

class Texture2D {
public:
	void load(std::string filename);
	GLuint m_ID;
	int width, height;
};