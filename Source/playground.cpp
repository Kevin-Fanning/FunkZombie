// playground.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#include "Renderer2d/Renderer2D.h"
#include "ResourceManager/ResourceManager.h"

int main(int argc, char* argv[])
{
	g_pApp = new FZApp();
	g_pApp->InitInstance(SCREEN_WIDTH, SCREEN_HEIGHT);

	int fontIndex = g_pApp->m_renderer->addFont("Assets/Arial.ttf", 20);
	int font2 = g_pApp->m_renderer->addFont("Assets/HARNGTON.TTF", 30);

	Resource snd("Assets/guitar.wav");
	g_pApp->m_resMan->getHandle(&snd);
	

	float xPos = 0;
	float speed = 100.0f;
	
	double circBuffer[120];
	int index = 0;
	double delta = 0;
	double lastFrame = 0;

	bool running = true;

	Texture2D tex1;
	tex1.load("Assets/thing.png", false);
	Texture2D tex2;
	tex2.load("Assets/thing2.png", false);

	std::wstring text = L"The quick brown fox jumped over the lazy dog.";

	float x = 0; float y = 0;
	int sx = 0; int sy = 0; int sw = 128; int sh = 128; int w = 256; int h = 256;
	while (running)
	{
		if (glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED))
		{
			running = false;
		}
		x+= 90.f * delta;
		y += 1.f * delta;
		h =  256*sinf(y);
		w =  256*cosf(y);

		g_pApp->m_renderer->clear(0.4f, 0.3f, 0.8f);
		g_pApp->m_renderer->beginBatch();


		g_pApp->m_renderer->draw(tex1, 512, 384, w, h, sx, sy, sw, sh, Color::White, 0.1f, x);
		g_pApp->m_renderer->draw(tex2, 64 + abs(768*sinf(y)), 200, 200, 200, Color::Green, 0.1f, x);

		g_pApp->m_renderer->drawString(fontIndex,
										text,
										(int)(1024/2 - g_pApp->m_renderer->stringSize(fontIndex, text)/2.f),
										400,
										Color::Red);
		g_pApp->m_renderer->drawString(font2,
										text,
										(int)(1024/2 - g_pApp->m_renderer->stringSize(font2, text)/2.f),
										200,
										Color::Yellow);
		g_pApp->m_renderer->endBatch();

		glfwSwapBuffers();

		double curTime = glfwGetTime();
		delta = curTime - lastFrame;
		lastFrame = curTime;
		circBuffer[index] = delta;
		++index;
		if (index > 119) {
			double avg = 0;
			for (int i = 0; i < 120; ++i)
			{
				avg += circBuffer[i];
			}
			avg /= 120;
			index = 0;
			//std::cout << 1 / avg << std::endl;
		}
	}
	delete g_pApp;
	return 0;
}

