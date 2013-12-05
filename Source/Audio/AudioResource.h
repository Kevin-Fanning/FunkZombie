#pragma once

#include <memory>
#include "../ResourceManager/ResourceManager.h"

class SoundExtraData : public IResourceExtraData
{
	friend class WaveResourceLoader;
public:
	std::string VToString();

protected:
	int m_lengthMilli;
};

class WaveResourceLoader : public IResourceLoader
{
public:
	int VBufferLength(char *rawBuffer, int bufferLength);
	bool VLoadResource(char *rawBuffer, int bufferLength, ResHandle* handle);
	char* VGetFileExtension();
};