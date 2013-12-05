/*
 * FZombie Game Engine
 * Font Class
 * Kevin Fanning
 * 2013
*/
#pragma once
#include FT_FREETYPE_H


//Holds all of the information for one character in a font
struct CharInfo
{
	float ax; // advance.x
	float ay; // advance.y
 
	float bw; // bitmap.width;
	float bh; // bitmap.rows;
 
	float bl; // bitmap_left;
	float bt; // bitmap_top;
 
	float tx; // x offset of glyph in texture coordinates
	float ty; // y offset of glyph in texture coordinates
};

//Class used by the font manager to hold font information
class Font
{
public:
	Font(int);
	~Font(void);

	//Initialize font from ttf file
	void init(const FT_Library &library, const std::string &filename);

	//Gives the pixel length of a string in this font
	unsigned int strlength(const std::wstring &);

	std::string m_name;
	FT_Face m_face;
	GLuint m_atlas;
	unsigned int m_fontSize;
	std::vector<CharInfo> m_charInfo;
};

