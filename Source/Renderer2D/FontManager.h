/*
 * FZombie Game Engine
 * Font Manager
 * Kevin Fanning
 * 2013
*/
#pragma once
#include "Font.h"

typedef std::shared_ptr<Font> StrongFontptr;
typedef std::vector<StrongFontptr> FontArray;

//FontManager class. Used by the renderer to create and render 
//font textures and render strings to the screen
class FontManager
{
public:
	FontManager(void);
	~FontManager(void);

	void init();

	//Add a font to the library
	int addFont(std::string filename, int fontSize);

	//Gets the font index from collection of initialized fonts.
	unsigned int getFontIndex(std::string name);

	//Use a font index to get a ptr to the font
	StrongFontptr getFont(unsigned int index);

protected:
	FT_Library m_fontLibrary;

	//Array to hold all of the fonts
	FontArray m_fonts;
};

