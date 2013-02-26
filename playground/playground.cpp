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


		g_pApp->m_renderer->clear(0.4f, 0.3f, 0.8f);

		g_pApp->m_renderer->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		g_pApp->m_renderer->draw("thing.png", xPos, 110, 256, 256);

		g_pApp->m_renderer->setColor(glm::vec4(1.0f, 0.5f, 0.3f, 1.0f));
		g_pApp->m_renderer->draw(100, xPos, 128, 128);

		g_pApp->m_renderer->setColor(glm::vec4(1.f, 1.f, 1.f, 0.4f));
		g_pApp->m_renderer->draw(xPos, xPos, 64, 64);

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
	return 0;
}

