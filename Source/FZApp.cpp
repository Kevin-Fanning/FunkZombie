/*
 * FZombie Game Engine
 * Main Class
 * Kevin Fanning
 * 9/13
 */

#include "stdafx.h"
#include "FZApp.h"

//Global pointer to the app
FZApp *g_pApp = nullptr;

//Void constructer just sets the global pointer to this instance
FZApp::FZApp(void)
{
	g_pApp = this;
	m_screenWidth = 0;
	m_screenHeight = 0;

	m_resMan = nullptr;
	m_renderer = nullptr;
}

/* Initializes the application and all of the components
 * @param screenWidth the width of the requested window
 * @param screenHeight the height of the requested window
*/
bool FZApp::InitInstance(int screenWidth, int screenHeight)
{
	//These calls all initialize glfw (the gl and windowing agent)
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
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//These calls created the renderer and intialize it
	m_renderer = std::unique_ptr<Renderer2D>(new Renderer2D());
	m_renderer->Init(screenWidth, screenHeight);

	//Initialize the resource manager
	m_resMan = std::unique_ptr<ResourceManager>(new ResourceManager());

	std::shared_ptr<IResourceLoader> loader(new WaveResourceLoader());
	m_resMan->RegisterLoader(loader);

	m_isRunning = true;
	return true;
}