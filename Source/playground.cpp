// playground.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#include "Renderer2d/Renderer2D.h"
#include "Resource Manager/ResourceManager.h"

int main(int argc, char* argv[])
{
	g_pApp = new FZApp();
	g_pApp->InitInstance(SCREEN_WIDTH, SCREEN_HEIGHT);

	int fontIndex = g_pApp->m_renderer->addFont("Assets/Arial.ttf", 20);
	int font2 = g_pApp->m_renderer->addFont("Assets/impact.ttf", 30);

	float xPos = 0;
	float speed = 100.0f;
	
	double circBuffer[30];
	int index = 0;
	double delta = 0;
	double lastFrame = 0;

	bool running = true;

	Texture2D tex1;
	tex1.load("Assets/thing.png");
	Texture2D tex2;
	tex2.load("Assets/thing2.png");

	std::wstring text = L"The quick brown fox jumped over the lazy dog.";


	int sx = 0; int sy = 0; int sw = 128; int sh = 128; int w = 128; int h = 128;
	while (running)
	{
		if (glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED))
		{
			running = false;
		}
		
		g_pApp->m_renderer->clear(0.4f, 0.3f, 0.8f);
		g_pApp->m_renderer->beginBatch();

		Color::White;

		g_pApp->m_renderer->draw(tex1, 50, 50, w, h, sx, sy, sw, sh, Color::White);
		g_pApp->m_renderer->draw(tex2, 200, 200, 200, 200, Color::Magenta);

		g_pApp->m_renderer->drawString(fontIndex,
										text,
										(int)(1024/2 - g_pApp->m_renderer->stringSize(fontIndex, text)/2.f),
										400,
										Color::Yellow);
		g_pApp->m_renderer->drawString(font2,
										text,
										(int)(1024/2 - g_pApp->m_renderer->stringSize(font2, text)/2.f),
										200,
										Color::Black);
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

