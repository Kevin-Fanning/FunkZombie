#include "stdafx.h"
#include "ResourceManager.h"


ResourceManager::ResourceManager(void)
{
}


ResourceManager::~ResourceManager(void)
{
	for (std::map<std::string, int>::iterator i = m_resources.begin(); i != m_resources.end(); i++)
	{
		glDeleteTextures(1, (GLuint*)&((*i).second));
	}
}

GLuint ResourceManager::getHandle(Resource* r)
{
	GLuint handle(find(r));
	if (handle == 0)
	{
		handle = load(r);
	}
	return handle;
}

//This function takes a resource string and returns a GLuint corresponding to the texture (now in memory)
GLuint ResourceManager::load(Resource* r)
{
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	int height, width;
	unsigned char* img = SOIL_load_image(r->m_name.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img);
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	m_resources[r->m_name] = texID;
	return texID;
}

GLuint ResourceManager::find(Resource* r)
{
	auto name = m_resources.find(r->m_name);
	if (name == m_resources.end())
	{
		return 0;
	}
	else
	{
		return name->second;
	}
}