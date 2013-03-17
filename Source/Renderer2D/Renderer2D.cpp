#include "stdafx.h"
#include "Renderer2D/Renderer2D.h"
#include "Resource Manager/Resource.h"
#include "Renderer2D/Texture2D.h"

Renderer2D::Renderer2D(void)
{
}


Renderer2D::~Renderer2D(void)
{
}

/**
*Initializes the renderer
* @param screenWidth The width of your screen
* @param screenHeight The height of your screen
*/
void Renderer2D::Init(int screenWidth, int screenHeight)
{
	m_fonts.init();
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	//Generate some buffers for the renderer to use
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	//Create and link a shader program with some hard coded shaders
	m_shaderProgram.createProgram();
	m_shaderProgram.loadShader(GL_VERTEX_SHADER, "Assets/VertexShader.glsl");
	m_shaderProgram.loadShader(GL_FRAGMENT_SHADER, "Assets/FragmentShader.glsl");
	m_shaderProgram.finalize();
	m_shaderProgram.useProgram();

	m_stringShaderProgram.createProgram();
	m_stringShaderProgram.loadShader(GL_VERTEX_SHADER, "Assets/VertexShader.glsl");
	m_stringShaderProgram.loadShader(GL_FRAGMENT_SHADER, "Assets/StringFragmentShader.glsl");
	m_stringShaderProgram.finalize();

	isText = false;

	//Tell the shader we are using TEXTURE0
	glUniform1i(m_shaderProgram.getSamplerLocation(), 0);

	//Let us use alpha textures
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_batchBegun = false;
	m_numQueSprites = 0;

	m_vertices.reserve(MAX_SPRITES * VERTICES_PER_SPRITE);
	m_spriteInfo.reserve(MAX_SPRITES);

	//The indices never change, even if we don't use all of them.
	//It makes sense to just load them all now and save the work later
	m_indices.reserve(MAX_SPRITES * 2 * 3);
	for (int i = 0; i < MAX_SPRITES * VERTICES_PER_SPRITE; i += VERTICES_PER_SPRITE)
	{
		m_indices.push_back(i);
		m_indices.push_back(i+2);
		m_indices.push_back(i+1);
		m_indices.push_back(i+1);
		m_indices.push_back(i+2);
		m_indices.push_back(i+3);
	}
}

/**
* Clears the color and depth buffer
* @param r  The red component of the clear  from 0.0 to 1.0
* @param g  The green component of the clear from 0.0 to 1.0
* @param b  The blue componenet of the clear from 0.0 to 1.0
*/
void Renderer2D::clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
* Begin the sprite batch
*/
void Renderer2D::beginBatch()
{
	if (m_batchBegun)
	{
		std::cout << "Batch has already begun" << std::endl;
		return;
	}

}

/**
* Draw a texture at a screen position, with a size
* @param tex a Texture2D object. Must have already been loaded
* @param x The x position in pixel coordinates. 0 is the left
* @param y The y position in pixel coordinates. 0 is the top
* @param w The width of the render on-screen in pixels
* @param h The height of the render on-screen in pixels
* @param color The color tint to draw the texture. Use Color::White for no tint
*/
void Renderer2D::draw(Texture2D tex, int x, int y, int w, int h, Color color)
{
	m_spriteInfo.push_back(SpriteInfo(tex.m_ID, x, y, w, h, w, h, 0, 0, w, h, color.r, color.g, color.b, false));
}

/**
* Draw a sub-image of a texture at a screen position, with a size
* @param tex a Texture2D object. Must have already been loaded
* @param x The x position in pixel coordinates. 0 is the left
* @param y The y position in pixel coordinates. 0 is the top
* @param w The width of the render on-screen in pixels
* @param h The height of the render on-screen in pixels
* @param sx The position of the sub-image in the original texture
* @param sy The y position of the sub-image in the original texture
* @param sw The width of the sub-image
* @param color The color tint to draw the texture. Use Color::White for no tint
*/
void Renderer2D::draw(Texture2D tex, int x, int y, int w, int h, int sx, int sy, int sw, int sh, Color color)
{
	m_spriteInfo.push_back(SpriteInfo(tex.m_ID, x, y, w, h, tex.width, tex.height, sx, sy, sw, sh, color.r, color.g, color.b, false));
}

/**
* Adds a font to the renderer's font collection
* @param fontName  a string representing the location/name of the font to load
* @param fontSize  the size of the font in pixels
* @returns An index referring to the font to be used later
*/
int Renderer2D::addFont(const std::string& fontName, int fontSize)
{
	return m_fonts.addFont(fontName, fontSize);
}

/**
* Utility function to get the pixel width of a string
* @param fontIndex integer referring to an already loaded font
* @param text  the string to be measured
*/
int Renderer2D::stringSize(int fontIndex, const  std::wstring& text)
{
	StrongFontptr font = m_fonts.getFont(fontIndex);
	return font->strlength(text);
}

/**
*  Draws a unicode string to the window
* @param fontIndex  integer referring to an already loaded font
* @param str  The unicode string to draw
* @param x    The x position of the text in screen coordinates
* @param y    The y position of the text in screen coordinates
*/
void Renderer2D::drawString(int fontIndex,const std::wstring& str, int x, int y, Color color)
{
	StrongFontptr font = m_fonts.getFont(fontIndex);
	int penX = x;
	int penY = y;
	for (unsigned int i = 0; i < str.length(); ++i)
	{
		int code = (unsigned int)str[i] - 32;
		if (code < font->m_face->num_glyphs){
			CharInfo info = font->m_charInfo[code];
			if (str[i] == ' ')
			{
				penX += (int)info.ax;
			}
			else
			{
				m_spriteInfo.push_back(SpriteInfo(font->m_atlas, penX + info.bl, penY - info.bt, info.bw, info.bh, 1024, 1024, info.tx, info.ty, info.bw, info.bh, color.r, color.g, color.b, true));
				penX += (int)info.ax;
			}
		}
	}
}

/**
* Ends the spritebatch and draws all sprites to the screen
*/
void Renderer2D::endBatch()
{
	//sort by texture
	std::sort(m_spriteInfo.begin(), m_spriteInfo.begin() + m_spriteInfo.size(), [](SpriteInfo const x, SpriteInfo const y) -> bool
            {
				return x.texID < y.texID;
            });

	//Go through the spriteInfo array, and if the texture changes, render what we have so far
	GLuint curTex = 0;
	for (unsigned int i = 0; i < m_spriteInfo.size(); ++i)
	{
		if (m_spriteInfo[i].texID != curTex)
		{
			//Render what we got

			//Tell the renderer to use the text shader if necessary
			if (i > 0)
				isText = m_spriteInfo[i-1].isText;

			renderBatch();
			m_numQueSprites = 0;
			curTex = m_spriteInfo[i].texID;
			useTexture(curTex);
		}
		//add this to the buffer
		addSpriteVertices(m_spriteInfo[i]);
		m_numQueSprites++;
	}
	//Render the remaining sprites
	isText = m_spriteInfo[m_spriteInfo.size()-1].isText;
	renderBatch();
	m_numQueSprites = 0;
	m_spriteInfo.clear();
}

/**
* Takes a sprite and creates 4 vertices to send to the renderer
* @param si  The sprite to convert into verts and send
*/
void Renderer2D::addSpriteVertices(SpriteInfo si)
{
	float posX = 2.0f * si.x / m_screenWidth - 1.0f;
	float posY = -2.0f/ m_screenHeight * si.y + 1;

	float scaleX = 2.f * si.w / m_screenWidth;
	float scaleY = 2.f * si.h / m_screenHeight;

	float uvPosx = float(si.sx) / si.imgX;
	float uvPosy = float(si.sy) / si.imgY;

	float uvScaleX = float(si.sw) / si.imgX;
	float uvScaleY = float(si.sh) / si.imgY;

	float top = posY;
	float bot = posY - scaleY;
	float left = posX;
	float right = posX + scaleX;

	Vertex TopLeft(
		glm::vec3(left, top, 0.f),
		glm::vec3(si.r, si.g, si.b),
		glm::vec2(uvPosx, uvPosy)
	);

	Vertex TopRight(
		glm::vec3(right, top, 0.f),
		glm::vec3(si.r, si.g, si.b),
		glm::vec2(uvPosx + uvScaleX, uvPosy)
	);

	Vertex BotLeft(
		glm::vec3(left, bot, 0.f),
		glm::vec3(si.r, si.g, si.b),
		glm::vec2(uvPosx, uvPosy + uvScaleY)
	);

	Vertex BotRight(
		glm::vec3(right, bot, 0.f),
		glm::vec3(si.r, si.g, si.b),
		glm::vec2(uvPosx + uvScaleX, uvPosy + uvScaleY)
	);
	m_vertices.push_back(TopLeft);
	m_vertices.push_back(TopRight);
	m_vertices.push_back(BotLeft);
	m_vertices.push_back(BotRight);
}

/**
* Switches the texture that OpenGL is using
* @param texID  handle referring to an openGL texture
*/
void Renderer2D::useTexture(GLuint texID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glUniform1i(m_shaderProgram.getSamplerLocation(), 0);
}

/**
* Renders a batch of sprites that share a texture
*
*/
void Renderer2D::renderBatch()
{
	//Give the data to the gpu and render. Obviously this is a waste if there is nothing to draw
	if (m_vertices.size() > 0)
	{
		if (isText) 
		{
			m_stringShaderProgram.useProgram();
		}
		else 
		{ 
			m_shaderProgram.useProgram(); 
		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*VERTEX_SIZE*m_vertices.size(), &m_vertices[0], GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*6*m_numQueSprites, &m_indices[0], GL_DYNAMIC_DRAW);
		m_shaderProgram.enableVertexAttribArray();

		glActiveTexture(GL_TEXTURE0);
		glDrawElements(GL_TRIANGLES, m_numQueSprites*6, GL_UNSIGNED_INT, 0);

		m_shaderProgram.disableVertexAttribArray();

		m_vertices.clear();
	}
}