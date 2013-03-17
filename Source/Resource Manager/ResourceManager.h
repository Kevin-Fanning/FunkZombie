#pragma once
#include <map>
#include <memory>
#include "Resource.h"

class ResourceManager;

class IResourceExtraData
{
public:
	virtual std::string VToString()=0;
};

class TextureExtraData : public IResourceExtraData
{
public:
	virtual std::string VToString() { return "Texture Extra Data"; }
	void Load();
	GLuint texID;
	int width, height;
};

class ResHandle 
{
	friend class ResourceManager;

public:
	ResHandle(Resource &resource, unsigned char* buffer, int size, ResourceManager *resMan);
	~ResHandle();

	unsigned char* getBuffer() { return m_buffer;}
	std::string getName() { return m_resource.m_name;}
	int getSize() {return m_size;}
	int getIsFreed() { return isFreed;}
	std::shared_ptr<IResourceExtraData> getExtra() {return m_extra;}

protected:
	Resource m_resource;
	unsigned char* m_buffer;
	int m_size;
	std::shared_ptr<IResourceExtraData> m_extra;
	bool isFreed;
};

class ResourceManager
{
	friend class ResHandle;

public:
	ResourceManager(void);
	~ResourceManager(void);

	std::shared_ptr<ResHandle> load(Resource* r);
	//unsigned char** load(Resource* r);
	std::shared_ptr<ResHandle> find(Resource* r);
	void free(std::string);

	std::shared_ptr<ResHandle> getHandle(Resource* r);

protected:
	std::map<std::string, std::shared_ptr<ResHandle>> m_resources;
};

