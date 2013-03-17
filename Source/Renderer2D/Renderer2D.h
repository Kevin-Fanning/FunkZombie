#pragma once

#include "ShaderProgram.h"
#include "SpriteInfo.h"
#include "Vertex.h"
#include "FontManager.h"
#include "Texture2D.h"

#define MAX_SPRITES 2048
#define VERTEX_SIZE 8
#define VERTICES_PER_SPRITE 4

class Renderer2D
{
public:
	Renderer2D(void);
	~Renderer2D(void);

	void Init(int screenWidth, int screenHeight);

	void beginBatch();

	void clear(float r, float g, float b);

	void draw(Texture2D tex, int x, int y, int w, int h, Color color);
	void draw(Texture2D tex, int x, int y, int w, int h, int sx, int sy, int sw, int sh, Color color);

	void draw(int x, int y, int w, int h, int depth);

	int addFont(const std::string& fontName, int fontSize);
	int stringSize(int fontIndex,const std::wstring& text);
	void drawString(int fontIndex,const std::wstring& text, int x, int y, Color color);

	void endBatch();

protected:

	void useTexture(GLuint texID);
	void addSpriteVertices(SpriteInfo si);
	void renderBatch();

	GLuint m_VBO;
	GLuint m_IBO;
	ShaderProgram m_shaderProgram;
	ShaderProgram m_stringShaderProgram;
	FontManager m_fonts;
	bool isText;

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

