#pragma once
#include "GameObject.h"
class Texture :
	public IComponent
{
public:
	Texture(void);
	~Texture(void);

	void VInit();
};

