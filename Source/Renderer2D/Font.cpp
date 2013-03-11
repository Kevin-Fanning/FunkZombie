#include "stdafx.h"
#include "Font.h"

#define FONT_TEX_SIZE 1024

Font::Font(int fontSize) : m_fontSize(fontSize)
{
}


Font::~Font(void)
{
}

void Font::init(const FT_Library &library, const std::string &filename)
{
	m_charInfo.reserve(128);
	FT_New_Face(library, filename.c_str(), 0, &m_face);
	FT_Set_Pixel_Sizes(m_face, 0, m_fontSize);

	int atlasWidth = 0; int rowHeight = 0;
	for (int i = 32; i < m_face->num_glyphs; ++i)
	{
		FT_Load_Char(m_face, i, FT_LOAD_RENDER);
		m_charInfo.push_back(CharInfo());

		m_charInfo[i-32].ax = (float)(m_face->glyph->advance.x >> 6);
		m_charInfo[i-32].ay = (float)(m_face->glyph->advance.y >> 6);
		m_charInfo[i-32].bh = (float)(m_face->glyph->bitmap.rows);
		m_charInfo[i-32].bw = (float)(m_face->glyph->bitmap.width);
		m_charInfo[i-32].bt = (float)(m_face->glyph->bitmap_top);
		m_charInfo[i-32].bl = (float)(m_face->glyph->bitmap_left);

		atlasWidth += m_face->glyph->bitmap.width;
		rowHeight = std::max(rowHeight, m_face->glyph->bitmap.rows);
	}

	glGenTextures(1, &m_atlas);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_atlas);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, FONT_TEX_SIZE, FONT_TEX_SIZE, 0, GL_ALPHA, GL_UNSIGNED_BYTE,0);
	
	int x = 0; int curRow = 0;
	for (int i = 32; i < m_face->num_glyphs; ++i)
	{
		FT_Load_Char(m_face, i, FT_LOAD_RENDER);
		if (m_face->glyph->bitmap.buffer && m_face->glyph->bitmap.width > 0)
		{
			if (x + m_face->glyph->bitmap.width+1 > FONT_TEX_SIZE)
			{
				curRow++;
				x = 0;
			}
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, curRow*rowHeight, m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, m_face->glyph->bitmap.buffer);
			m_charInfo[i-32].tx = x;
			m_charInfo[i-32].ty = curRow*rowHeight;
			x += m_face->glyph->bitmap.width + 1;
		}
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}