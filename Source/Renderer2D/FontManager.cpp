#include "stdafx.h"
#include "FontManager.h"


FontManager::FontManager(void)
{
}

FontManager::~FontManager(void)
{
}

void FontManager::init()
{
	if (FT_Init_FreeType(&m_fontLibrary))
	{
		assert(0 && "Font library unable to initialize");
	}
}

int FontManager::addFont(std::string filename, int fontSize)
{
	std::shared_ptr<Font> font(new Font(fontSize));
	font->init(m_fontLibrary, filename);
	m_fonts.push_back(font);
	return m_fonts.size() - 1;
}

StrongFontptr FontManager::getFont(unsigned int index)
{
	return m_fonts[index];
}
