#pragma once
#include FT_FREETYPE_H



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

class Font
{
public:
	Font(int);
	~Font(void);

	void init(const FT_Library &library, const std::string &filename);

	std::string m_name;
	FT_Face m_face;
	GLuint m_atlas;
	unsigned int m_fontSize;
	std::vector<CharInfo> m_charInfo;
};

