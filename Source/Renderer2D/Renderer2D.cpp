#include "stdafx.h"
#include "Renderer2D.h"
#include "Resource.h"

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
	//TEMP CODE
	m_fonts.init();
	arialID = m_fonts.addFont("Assets/Arial.ttf", 25);
	//END TEMP CODE
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

void Renderer2D::beginBatch()
{
	if (m_batchBegun)
	{
		std::cout << "Batch has already begun" << std::endl;
		return;
	}

}
void Renderer2D::draw(unsigned int texID,int x,int y,int w,int h)
{
	m_spriteInfo.push_back(SpriteInfo(texID, x, y, w, h, w, h, 0, 0, w, h, 1.f, 1.f, 1.f));
}

void Renderer2D::draw(unsigned int texID,int x,int y,int w,int h, int sx,int sy,int sw,int sh,float r,float g,float b)
{
	m_spriteInfo.push_back(SpriteInfo(texID, x, y, w, h, w, h, sx, sy, sw, sh, r, g, b));
}

void Renderer2D::drawString(std::wstring str, int x, int y)
{
	std::shared_ptr<Font> arial = m_fonts.getFont(arialID);
	int penX = x;
	int penY = y;
	for (int i = 0; i < str.length(); ++i)
	{
		unsigned int code = (unsigned int)str[i] - 32;
		CharInfo info = arial->m_charInfo[code];
		if (str[i] == ' ')
		{
			penX += info.ax;
		}
		else
		{
			m_spriteInfo.push_back(SpriteInfo(arial->m_atlas, penX + info.bl, penY - info.bt, info.bw, info.bh, 1024, 1024, info.tx, info.ty, info.bw, info.bh, 1.f, 1.f, 1.f));
			penX += info.ax;
		}
	}
}

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
	renderBatch();
	m_numQueSprites = 0;
	m_spriteInfo.clear();
}

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

void Renderer2D::useTexture(GLuint texID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glUniform1i(m_shaderProgram.getSamplerLocation(), 0);
}

void Renderer2D::renderBatch()
{
	//Give the data to the gpu and render. Obviously this is a waste if there is nothing to draw
	if (m_vertices.size() > 0)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*VERTEX_SIZE*m_vertices.size(), &m_vertices[0], GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*6*m_numQueSprites, &m_indices[0], GL_DYNAMIC_DRAW);
		m_shaderProgram.enableVertexAttribArray();

		glActiveTexture(GL_TEXTURE0);
		glDrawElements(GL_TRIANGLES, m_numQueSprites*6, GL_UNSIGNED_INT, 0);

		m_shaderProgram.disableVertexAttribArray();

		m_vertices.clear();
	}
}