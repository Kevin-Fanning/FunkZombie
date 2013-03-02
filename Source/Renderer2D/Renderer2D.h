#pragma once

#include "ShaderProgram.h"
#include "SpriteInfo.h"
#include "Vertex.h"
#include "FontManager.h"

#define MAX_SPRITES 2048
#define VERTEX_SIZE 8
#define VERTICES_PER_SPRITE 4

class Renderer2D
{
public:
	Renderer2D(void);
	~Renderer2D(void);

	void Init(int screenWidth, int screenHeight);

	void setColor(glm::vec4 color);
	void setColor(float r, float g, float b);

	void beginBatch();

	void clear(float r, float g, float b);

	void draw(unsigned int texID, int x, int y, int w, int h, int sx, int sy, int sw, int sh, float r, float g, float b);
	void draw(std::string filename, int x, int y, int w, int h, int sx, int sy, int sw, int sh, float r, float g, float b);
	void draw(unsigned int texID, int x, int y, int w, int h);
	void draw(std::string filename, int x, int y, int w, int h);
	void draw(int x, int y, int w, int h, int depth);

	void drawString(std::wstring, int x, int y);

	void endBatch();

protected:

	void useTexture(GLuint texID);
	void addSpriteVertices(SpriteInfo si);
	void renderBatch();

	GLuint m_VBO;
	GLuint m_IBO;
	ShaderProgram m_shaderProgram;
	FontManager m_fonts;
	int arialID;

	int m_screenWidth;
	int m_screenHeight;

	glm::mat4 transformation;

	int m_curDepth;

	
	bool m_batchBegun;
	int m_numQueSprites;

	std::vector<SpriteInfo> m_spriteInfo;
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices; 
};

