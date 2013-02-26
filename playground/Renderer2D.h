#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <memory>

#include "ShaderProgram.h"

class Renderer2D
{
public:
	Renderer2D(void);
	~Renderer2D(void);

	void Init(int screenWidth, int screenHeight);

	void setColor(glm::vec4 color);
	void setColor(float r, float g, float b);

	void clear(float r, float g, float b);

	void draw(int x, int y, int w, int h);
	void draw(std::string filename, int x, int y, int w, int h);
	void draw(int x, int y, int w, int h, int depth);

protected:
	void useTexture(GLuint texID);

	GLuint m_VBO;
	ShaderProgram m_shaderProgram;

	int m_screenWidth;
	int m_screenHeight;

	glm::mat4 transformation;

	int m_curDepth;

	static float vertices[30];
};

