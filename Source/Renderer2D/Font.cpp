/*
 * FZombie Game Engine
 * Font code
 * Kevin Fanning
 * 2013
*/

#include "stdafx.h"
#include "Font.h"

//This is the size of the texture the font engine will render to
#define FONT_TEX_SIZE 1024

/*
 * Creates a new Font
 * @param fontSize the size of the font on the screen
*/
Font::Font(int fontSize) : m_fontSize(fontSize)
{
}


Font::~Font(void)
{
}

/*
 * Initializes the font with a supplied ttf fontface
 * @param library The FreeType library from the FontManager
 * @param filename the name of the file to load
*/
void Font::init(const FT_Library &library, const std::string &filename)
{
	m_name = filename;

	//Make sure the vector doesn't have to resize in the middle of this. (at least for ascii)
	m_charInfo.reserve(128);

	//Request a new font face from FreeType. return early if failure
	if (FT_New_Face(library, filename.c_str(), 0, &m_face))
		{ return; }

	//Tell FT what pixel size we want for the font
	FT_Set_Pixel_Sizes(m_face, 0, m_fontSize);

	//The reason this starts at 32 is to avoid needlessly copying non-printables in ascii
	//This loop stops after FT says there are no more characters
	//This whole loop is just to populate the charInfo array. No rendering yet
	int atlasWidth = 0; int rowHeight = 0;
	for (int i = 32; i < m_face->num_glyphs; ++i)
	{
		//Ask FT to give us the next character and then I put it into the array
		FT_Load_Char(m_face, i, FT_LOAD_RENDER);
		m_charInfo.push_back(CharInfo());

		//The actual characters start at 32, but I want the array to start at 0
		m_charInfo[i-32].ax = (float)(m_face->glyph->advance.x >> 6); //How far from start until the next char should start
		m_charInfo[i-32].ay = (float)(m_face->glyph->advance.y >> 6); //How far from start vertically (mostly zero in english)
		m_charInfo[i-32].bh = (float)(m_face->glyph->bitmap.rows);	  //How high in pixels the char is
		m_charInfo[i-32].bw = (float)(m_face->glyph->bitmap.width);   //How wide in pixels the char is
		m_charInfo[i-32].bt = (float)(m_face->glyph->bitmap_top);     //
		m_charInfo[i-32].bl = (float)(m_face->glyph->bitmap_left);    //

		//I need to know how wide all the chars together are, and what the tallest character is
		//To make a clean font atlas.
		atlasWidth += m_face->glyph->bitmap.width;
		rowHeight = std::max(rowHeight, m_face->glyph->bitmap.rows);
	}

	//Here I am creating a new texture in openGL and binding a new texture so that I can draw to it
	glGenTextures(1, &m_atlas);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_atlas);
	
	//I need GL to store pixels by byte alignment, not word(the default)
	//Because I'm only storing alpha
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Tells GL that I have unsigned bytes of only alpha and am storing them in luminance and alpha style.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, FONT_TEX_SIZE, FONT_TEX_SIZE, 0, GL_ALPHA, GL_UNSIGNED_BYTE,0);
	
	//Now I'm finally rendering the font texture.
	int x = 0; int curRow = 0;
	for (int i = 32; i < m_face->num_glyphs; ++i)
	{
		//Yeah I'm doing it twice. I couldn't render earlier because I didn't have max height or width
		FT_Load_Char(m_face, i, FT_LOAD_RENDER);

		//Basically if the glyph has a drawable char
		if (m_face->glyph->bitmap.buffer && m_face->glyph->bitmap.width > 0)
		{
			//This checks if I need to start a new row
			if (x + m_face->glyph->bitmap.width+1 > FONT_TEX_SIZE)
			{
				curRow++;
				x = 0;
			}
			//This call tells gl to print the char to the texture buffer (the atlas)
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, curRow*rowHeight, m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, m_face->glyph->bitmap.buffer);
			
			//Collect some information so I know where to print the next char
			m_charInfo[i-32].tx = (float)x;
			m_charInfo[i-32].ty = (float)curRow*rowHeight;
			x += m_face->glyph->bitmap.width + 1;
		}
	}
	//Just resetting some gl params I changed
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

/*
 * strlength tells you  how long a string is in pixels
 * useful for centering text
 * @param in a string you want to know the pixel length of
 * 
 * @returns the pixel length of in
*/
unsigned int Font::strlength(const std::wstring &in)
{
	float len = 0;
	for (unsigned int i = 0; i < in.length(); ++i)
	{
		wchar_t wchar = in[i];
		len += m_charInfo[(int)wchar - 32].ax;
	}
	return (unsigned int)len;
}