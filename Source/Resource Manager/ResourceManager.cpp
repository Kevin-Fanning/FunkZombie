#include "stdafx.h"
#include "ResourceManager.h"


ResHandle::ResHandle(Resource & resource, unsigned char* buffer, int size, ResourceManager * resMan) :
	m_resource(resource), m_buffer(buffer), m_size(size), m_extra(nullptr) {}

ResourceManager::ResourceManager(void)
{
}

ResHandle::~ResHandle()
{
	int x = 0;
	m_extra.reset();
}

ResourceManager::~ResourceManager(void)
{
	/*for (std::map<std::string, ResHandle>::iterator i = m_resources.begin(); i != m_resources.end(); i++)
	{
		glDeleteTextures(1, (GLuint*)&((*i).second));
	}*/
}

std::shared_ptr<ResHandle> ResourceManager::getHandle(Resource* r)
{
	std::shared_ptr<ResHandle> handle(find(r));
	if (handle == nullptr)
	{
		handle = load(r);
	}
	return handle;
}

//This function takes a resource string and returns a resource handle
std::shared_ptr<ResHandle> ResourceManager::load(Resource* r)
{
	//TEMP SPECIFIC TO TEXTURE
	std::shared_ptr<TextureExtraData> extra(new TextureExtraData);

	glGenTextures(1, &(extra->texID));
	glBindTexture(GL_TEXTURE_2D, extra->texID);
	unsigned char* img = SOIL_load_image(r->m_name.c_str(), &(extra->width), &(extra->height), 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, extra->width, extra->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img);
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	std::shared_ptr<ResHandle> handle(new ResHandle(*r, img, 0, this));
	handle->isFreed = true;
	handle->m_extra = extra;

	m_resources[r->m_name] = handle;
	return handle;
	//END TEMP
}

//unsigned char** ResourceManager::load(Resource* r)
//{
//	int height, width;
//	unsigned char* img = SOIL_load_image(r->m_name.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
//	return &img;
//}

std::shared_ptr<ResHandle> ResourceManager::find(Resource* r)
{
	auto name = m_resources.find(r->m_name);
	if (name == m_resources.end())
	{
		return nullptr;
	}
	else
	{
		return name->second;
	}
}