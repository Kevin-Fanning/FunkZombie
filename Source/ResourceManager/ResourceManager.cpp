#include "stdafx.h"
#include "ResourceManager.h"
#include "GL/glew.h"
#include "GL/glfw.h"
#include "SOIL.h"
#include <fstream>
#include <iostream>


ResHandle::ResHandle(Resource & resource, unsigned char* buffer, int size, ResourceManager * resMan) :
	m_resource(resource), m_buffer(buffer), m_size(size), m_extra(nullptr) {}

void ResHandle::setExtra(std::shared_ptr<IResourceExtraData> extra)
{
	this->m_extra = extra;
}

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

}

void ResourceManager::RegisterLoader(std::shared_ptr<IResourceLoader> loader)
{
	m_loaders.push_back(loader);
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

//This function takes a resource string, loads it into memory, and returns a resource handle
std::shared_ptr<ResHandle> ResourceManager::load(Resource* r)
{
	std::shared_ptr<IResourceLoader> loader = nullptr;
	//First is to find and use the correct loader
	for (std::vector<std::shared_ptr<IResourceLoader>>::iterator it = m_loaders.begin(); it != m_loaders.end(); it++)
	{
		//std::cout << r->m_name.substr(r->m_name.length()-3) << " : " << (*it)->VGetFileExtension() << std::endl;
		if (r->m_name.substr(r->m_name.length()-3) == (*it)->VGetFileExtension())
		{
			loader = (*it);
		}
	}
	if (loader)
	{
		//Get the raw file into memory
		std::ifstream in(r->m_name, std::ios::binary | std::ios::in | std::ios::ate);
		int fileLength = in.tellg();
		std::cout << "File Length: " << fileLength << std::endl;
		in.seekg(0, std::ios::beg);

		char * rawBuffer = new char[fileLength];
		in.read(rawBuffer, fileLength);
		in.close();

		

		//Use the loader to load whatever file
		unsigned char* buffer;
		int bufferLength = loader->VBufferLength(rawBuffer, fileLength);
		buffer = new unsigned char[bufferLength];
		ResHandle* handle = new ResHandle(*r, buffer, bufferLength, this);
		loader->VLoadResource(rawBuffer, fileLength, handle);
		delete [] rawBuffer;

		handle->isFreed = false;
		//Add it to the hash table for resources so it won't get loaded twice.
		std::shared_ptr<ResHandle> ptrHandle(handle);
		m_resources[r->m_name] = ptrHandle;
		return ptrHandle;
	}
	else
	{
		//TEMP SPECIFIC TO TEXTURE. THIS IS THE TEXTURE LOADER
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

		std::shared_ptr<ResHandle> handle2(new ResHandle(*r, img, 0, this));
		handle2->isFreed = true;
		handle2->m_extra = extra;

		m_resources[r->m_name] = handle2;
		return handle2;
		//END TEMP
	}
}

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