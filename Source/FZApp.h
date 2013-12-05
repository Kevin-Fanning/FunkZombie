/*
	FZombie Game Engine
	Kevin Fanning
	2013
*/
#pragma once
#include "Renderer2D/Renderer2D.h"
#include "ResourceManager/ResourceManager.h"
#include "Audio/AudioResource.h"

/*
 * This is the class through which the engine is accessed in the main program
*/
class FZApp
{
public:
	FZApp();

	std::unique_ptr<Renderer2D> m_renderer;
	std::unique_ptr<ResourceManager> m_resMan;

	//Call this first, it starts and initializes all components
	bool InitInstance(int screenWidth, int screenHeight);

protected:
	int m_screenWidth, m_screenHeight;


	bool m_quitRequested;
	bool m_isQuitting;
	bool m_isRunning;
};

extern FZApp *g_pApp;