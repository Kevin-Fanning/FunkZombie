#pragma once
#include <map>
#include <memory>
#include "Resource.h"

class ResourceManager
{
public:
	ResourceManager(void);
	~ResourceManager(void);

	GLuint load(Resource* r);
	GLuint find(Resource* r);
	void free(std::string);

	GLuint getHandle(Resource* r);

protected:
	std::map<std::string, int> m_resources;
};

