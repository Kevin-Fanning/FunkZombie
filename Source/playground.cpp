// playground.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768


#include <GL/glew.h>
#include <GL/glfw.h>
#include <iostream>
#include <glm/glm.hpp>
#include <memory>
#include <SOIL.h>

#include "Renderer2d/Renderer2D.h"
#include "Resource Manager/ResourceManager.h"

int main(int argc, char* argv[])
{
	g_pApp = new FZApp();
	g_pApp->InitInstance(SCREEN_WIDTH, SCREEN_HEIGHT);

	int fontIndex = g_pApp->m_renderer->addFont("Assets/Arial.ttf", 20);

	float xPos = 0;
	float speed = 100.0f;
	
	double circBuffer[30];
	int index = 0;
	double delta = 0;
	double lastFrame = 0;

	bool running = true;

	GLuint tex1 = g_pApp->m_resMan->getHandle(&Resource("Assets/thing.png"));
	GLuint tex2 = g_pApp->m_resMan->getHandle(&Resource("Assets/thing2.png"));
	std::wstring text = L"The quick brown fox jumped over the lazy dog.";


	int x = 10;
	while (running)
	{
		if (glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED))
		{
			running = false;
		}
		if (glfwGetKey(GLFW_KEY_UP))
		{
			x = 60;
		}
		else 
		{
			x = 10;
		}
		
		g_pApp->m_renderer->clear(0.4f, 0.3f, 0.8f);
		g_pApp->m_renderer->beginBatch();
		g_pApp->m_renderer->draw(tex1, x, 10, 128, 128);
		g_pApp->m_renderer->draw(tex2, 200, 200, 50, 40);
		g_pApp->m_renderer->drawString(fontIndex,
										text,
										(int)(1024/2 - g_pApp->m_renderer->stringSize(fontIndex, text)/2.f),
										400);
		g_pApp->m_renderer->endBatch();

		glfwSwapBuffers();

		double curTime = glfwGetTime();
		delta = curTime - lastFrame;
		lastFrame = curTime;
		circBuffer[index] = delta;
		++index;
		if (index > 29) {
			double avg = 0;
			for (int i = 0; i < 30; ++i)
			{
				avg += circBuffer[i];
			}
			avg /= 30;
			index = 0;
		}
	}
	delete g_pApp;
	return 0;
}

