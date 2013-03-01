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

#include "Renderer2D.h"
#include "ResourceManager.h"

int main(int argc, char* argv[])
{
	g_pApp = new FZApp();
	g_pApp->InitInstance(SCREEN_WIDTH, SCREEN_HEIGHT);

	float xPos = 0;
	float speed = 100.0f;
	
	double circBuffer[30];
	int index = 0;
	double delta = 0;
	double lastFrame = 0;

	bool running = true;

	GLuint tex1 = g_pApp->m_resMan->getHandle(&Resource("Assets/thing.png"));
	GLuint tex2 = g_pApp->m_resMan->getHandle(&Resource("Assets/thing2.png"));

	while (running)
	{
		if (glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED))
		{
			running = false;
		}
		if (glfwGetKey(GLFW_KEY_UP))
		{
			xPos += speed * delta;
		}
		if (glfwGetKey(GLFW_KEY_DOWN))
		{
			xPos -= speed * delta;
		}
		g_pApp->m_renderer->clear(0.4f, 0.3, 0.8f);
		g_pApp->m_renderer->beginBatch();
		g_pApp->m_renderer->draw(tex1, 20, 20, 128, 128, 0, 0, 64, 64, 1.f, 1.f, 1.f );
		g_pApp->m_renderer->draw(tex1, 148, 20, 128, 128, 64, 0, 64, 64, 1.f, 1.f, 1.f);
		g_pApp->m_renderer->draw(tex2, 20, 20, 256, 256);
		g_pApp->m_renderer->draw(tex1, 20, 148, 128, 128, 0, 64, 64, 64, 1.f, 1.f, 1.f );
		g_pApp->m_renderer->draw(tex1, 148, 148, 128, 128, 64, 64, 64, 64, 1.f, 1.f, 1.f);
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

