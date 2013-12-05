/*
 * FZombie Game Engine
 * Texture Class
 * Kevin Fanning
 * 2013
*/
#pragma once

#include "ResourceManager/ResourceManager.h"

//This class holds all pertinent information for 2d textures.
class Texture2D {
public:
	Texture2D() : m_ID(0), width(0), height(0), isTransparent(false) {}
	Texture2D(GLuint texID, int _width, int _height, bool _isTransparent) :
		m_ID(texID), width(_width), height(_height), isTransparent(_isTransparent) {}

	// Call load after creating the texture to actually grab the resource
	void load(std::string filename, bool isTransparent);

	//The id allocated by the resource manager during load time
	GLuint m_ID;

	int width, height;
	bool isTransparent;
};