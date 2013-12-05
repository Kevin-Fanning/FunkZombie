/*
 * FZombie Game Engine
 * Renderer Component
 * Kevin Fanning
 * 2013
*/
#pragma once

#include "ShaderProgram.h"
#include "SpriteInfo.h"
#include "Vertex.h"
#include "FontManager.h"
#include "Texture2D.h"

#define MAX_SPRITES 2048
#define VERTEX_SIZE 8
#define VERTICES_PER_SPRITE 4

//This is the component that uses openGL to actually draw all of the pictures/fonts to the screen
class Renderer2D
{
public:
	Renderer2D(void);
	~Renderer2D(void);

	//Called by the engine at initialization to start up GL and the renderer
	void Init(int screenWidth, int screenHeight);

	//Starts the spriteBatch. (Currently only one at a time)
	void beginBatch();

	//Clears the screen
	void clear(float r, float g, float b);

	//These three functions push a sprite onto the batch, with a multitude of options
	void draw(Texture2D tex, int x, int y, int w, int h, Color color,float depth = 0.1f, float rotation = 0.f);
	void draw(Texture2D tex, int x, int y, int w, int h, int sx, int sy, int sw, int sh, Color color, float depth = 0.1f, float rotation = 0.f);
	void draw(Texture2D tex, int x, int y, int w, int h, int sx, int sy, int sw, int sh, Color color, float depth, float rotation, int rotCenterX, int rotCenterY);

	void draw(int x, int y, int w, int h, int depth);

	//Add a font to the library. Make sure to save the index
	int addFont(const std::string& fontName, int fontSize);

	//Get the size of a string in a loaded font
	int stringSize(int fontIndex,const std::wstring& text);
	//Draw a unicode string to the screen
	void drawString(int fontIndex,const std::wstring& text, int x, int y, Color color);

	//end batch and draw everything
	void endBatch();

protected:

	void useTexture(GLuint texID);
	void addSpriteVertices(SpriteInfo si);
	void flushSprites(std::vector<SpriteInfo> & sprites);
	void renderBatch();

	GLuint m_VBO;
	GLuint m_IBO;
	ShaderProgram m_shaderProgram;
	ShaderProgram m_stringShaderProgram;
	FontManager m_fonts;
	bool isText;

	int m_screenWidth;
	int m_screenHeight;
	
	bool m_batchBegun;
	int m_numQueSprites;

	std::vector<SpriteInfo> m_spriteInfo;
	std::vector<SpriteInfo> m_transparentSpriteInfo;
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices; 
};

