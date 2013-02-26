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
#include "ShaderProgram.h"

int main(int argc, char* argv[])
{
	if (glfwInit() == GL_FALSE)
	{
		std::cout << "GLFW init failed" << std::endl;
		return 1;
	}
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_VERSION_MINOR, 3);
	glfwOpenWindow(SCREEN_WIDTH, SCREEN_HEIGHT, 8, 8, 8, 8, 8, 0, GLFW_WINDOW);
	glfwSetWindowTitle("Playground");

	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew initalization failed" << std::endl;
		return 1;
	}
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	Renderer2D renderer;

	renderer.Init(SCREEN_WIDTH, SCREEN_HEIGHT);

	glClearColor(0.3f, 0.6f, 0.9f, 1.0f);
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


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		renderer.drawSquare(xPos, 110, 256, 256);

		renderer.setColor(glm::vec4(1.0f, 0.5f, 0.3f, 1.0f));
		renderer.drawSquare(100, xPos, 128, 128);

		renderer.setColor(glm::vec4(1.f, 1.f, 1.f, 0.4f));
		renderer.drawSquare(xPos, xPos, 64, 64);

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
			std::cout << 1 / avg << std::endl;
			index = 0;
		}
	}
	return 0;
}

