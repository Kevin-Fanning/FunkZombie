#include "stdafx.h"
#include "FZApp.h"

FZApp *g_pApp = nullptr;

FZApp::FZApp(void)
{
	g_pApp = this;
	m_screenWidth = 0;
	m_screenHeight = 0;

	m_resMan = nullptr;
	m_renderer = nullptr;
}


bool FZApp::InitInstance(int screenWidth, int screenHeight)
{
	if (glfwInit() == GL_FALSE)
	{
		std::cout << "GLFW init failed" << std::endl;
		return false;
	}
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_VERSION_MINOR, 1);
	glfwOpenWindow(screenWidth, screenHeight, 8, 8, 8, 8, 24, 0, GLFW_WINDOW);
	glfwSetWindowTitle("Playground");

	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew initalization failed" << std::endl;
		return false;
	}
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	m_renderer = std::unique_ptr<Renderer2D>(new Renderer2D());
	m_renderer->Init(screenWidth, screenHeight);

	m_resMan = std::unique_ptr<ResourceManager>(new ResourceManager());

	m_isRunning = true;
	return true;
}