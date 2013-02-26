#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <memory>

#include "ShaderProgram.h"
#include "Vertex.h"

class Renderer2D
{
public:
	Renderer2D(void);
	~Renderer2D(void);

	void Init(int screenWidth, int screenHeight);

	void setColor(glm::vec4 color);
	void setColor(float r, float g, float b);
	void drawSquare(int x, int y, int w, int h);
	void drawSquare(int x, int y, int w, int h, int depth);

protected:
	GLuint m_VBO;
	GLint m_posLocation;
	GLint m_colLocation;
	ShaderProgram m_shaderProgram;

	GLuint m_texID;

	int m_screenWidth;
	int m_screenHeight;

	glm::mat4 transformation;

	int m_curDepth;

	static float vertices[30];
};

