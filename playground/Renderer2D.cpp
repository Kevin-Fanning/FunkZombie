#include "stdafx.h"
#include "Renderer2D.h"
#include "Resource.h"

Renderer2D::Renderer2D(void)
{
}


Renderer2D::~Renderer2D(void)
{
}

void Renderer2D::Init(int screenWidth, int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	m_shaderProgram.createProgram();
	m_shaderProgram.loadShader(GL_VERTEX_SHADER, "VertexShader.glsl");
	m_shaderProgram.loadShader(GL_FRAGMENT_SHADER, "FragmentShader.glsl");
	m_shaderProgram.finalize();
	m_shaderProgram.useProgram();

	//glGenTextures(1, &m_texID);
	//glGenTextures(1, &m_texID2);
	//glActiveTexture(GL_TEXTURE0);

	//glBindTexture(GL_TEXTURE_2D, m_texID);
	//int height, width;
	//unsigned char* img = SOIL_load_image("thing.png", &width, &height, 0, SOIL_LOAD_RGBA);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	//SOIL_free_image_data(img);

	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glBindTexture(GL_TEXTURE_2D, m_texID2);
	//img = SOIL_load_image("thing2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	//SOIL_free_image_data(img);

	glUniform1i(m_shaderProgram.getSamplerLocation(), 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer2D::setColor(glm::vec4 color)
{
	glUniform4f(m_shaderProgram.getColLocation(), color.r, color.g, color.b, color.a);
}
void Renderer2D::setColor(float r, float g, float b)
{
	glUniform4f(m_shaderProgram.getColLocation(), r, g, b, 1.0f);
}

void Renderer2D::clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer2D::draw(int x, int y, int w, int h)
{
	float posX = 2.0f * x / m_screenWidth - 1.0f;
	float posY = 1.0f - 2.0f * y / m_screenHeight - 2.0f*h/m_screenHeight;

	glm::mat4 translation, scale;
	translation = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, 0));

	scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f * w / m_screenWidth,2.0f*h/m_screenHeight, 1.f));
	transformation = translation * scale;
	glUniformMatrix4fv(m_shaderProgram.getMVPLocation(), 1, GL_FALSE, &transformation[0][0]);
	glUniform1i(m_shaderProgram.getSamplerLocation(), 0);

	m_shaderProgram.enableVertexAttribArray();

	glActiveTexture(GL_TEXTURE0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	m_shaderProgram.disableVertexAttribArray();
}

void Renderer2D::draw(std::string name, int x, int y, int w, int h)
{
	GLuint texLocation = g_pApp->m_resMan->getHandle(&Resource(name));
	glBindTexture(GL_TEXTURE_2D, texLocation);
	draw(x, y, w, h);
}

void Renderer2D::draw(int x, int y, int w, int h, int depth)
{
	m_curDepth = depth;
	draw(x,y,w,h);
	m_curDepth = 0;
}

void Renderer2D::useTexture(GLuint texID)
{
	glBindTexture(GL_TEXTURE_2D, texID);
}

float Renderer2D::vertices[30] = {
		0.f,  1.f, 0.0f, 0.0f, 0.0f, // Top-left
		0.f, 0.f, 0.0f, 0.0f, 1.0f,  // Bottom-left
		1.f, 1.f, 0.0f, 1.0f, 0.0f, // Top-right
		1.f, 1.f, 0.0f, 1.0f, 0.0f, // Top-right
		0.f, 0.f, 0.0f, 0.0f, 1.0f,  // Bottom-left
		1.f, 0.f, 0.0f, 1.0f, 1.0f // Bottom-right
};