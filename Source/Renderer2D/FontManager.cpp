/*
 * FZombie Game Engine
 * FontManager implementation
 * Kevin Fanning
 * 2013
*/
#include "stdafx.h"
#include "FontManager.h"


FontManager::FontManager(void)
{
}

FontManager::~FontManager(void)
{
}

//Initializes FreeType to ready it to load fonts
void FontManager::init()
{
	if (FT_Init_FreeType(&m_fontLibrary))
	{
		assert(0 && "Font library unable to initialize");
	}
}

/*
 * Adds a font to the collection. IF the font is already added
 * it returns the index to the font
 *
 * @param filename the name of the ttf font in the filesystem
 * @param fontSize how large you want to render the font
 * @returns the index of the newly added font
*/
int FontManager::addFont(std::string filename, int fontSize)
{
	//Search to see if the font was already added
	for (int i = 0; i < m_fonts.size(); ++i)
	{
		if (m_fonts[i]->m_name == filename)
		{
			return i;
		}
	}

	//Create a new font and initialize it
	std::shared_ptr<Font> font(new Font(fontSize));
	font->init(m_fontLibrary, filename);
	m_fonts.push_back(font);
	return m_fonts.size() - 1;
}

/*
 * getFont returns a pointer to the font who has index 'index'
 * 
 * @param index the index of the font you want
 * @returns A shared pointer to the requested font
*/
StrongFontptr FontManager::getFont(unsigned int index)
{
	return m_fonts[index];
}

/*
 * getFontIndex searches the loaded fonts and tries to find
 * the requested string
 *
 * @param fileName the name of the file used to load the string
 * @returns index of the font, or -1 if not found
*/
unsigned int FontManager::getFontIndex(std::string fileName)
{
	for (int i = 0; i < m_fonts.size(); ++i)
	{
		if (m_fonts[i]->m_name == fileName)
		{
			return i;
		}
	}
	return -1;
}