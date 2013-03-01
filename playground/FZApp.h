#pragma once
#include "Renderer2D.h"
#include "ResourceManager.h"
class FZApp
{
public:
	FZApp();

	std::unique_ptr<Renderer2D> m_renderer;
	std::unique_ptr<ResourceManager> m_resMan;

	bool InitInstance(int screenWidth, int screenHeight);

protected:
	int m_screenWidth, m_screenHeight;


	bool m_quitRequested;
	bool m_isQuitting;
	bool m_isRunning;
};

extern FZApp *g_pApp;