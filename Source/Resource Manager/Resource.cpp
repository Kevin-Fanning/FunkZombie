#include "stdafx.h"
#include "Resource.h"

Resource::Resource(std::string name) : m_name(name)
{
	std::transform(m_name.begin(), m_name.end(), m_name.begin(), (int(*)(int))std::tolower);
}