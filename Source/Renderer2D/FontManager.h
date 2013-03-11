#pragma once
#include "Font.h"

typedef std::shared_ptr<Font> StrongFontptr;
typedef std::vector<StrongFontptr> FontArray;

class FontManager
{
public:
	FontManager(void);
	~FontManager(void);

	void init();

	int addFont(std::string filename, int fontSize);

	unsigned int getFontIndex(std::string name);
	StrongFontptr getFont(unsigned int index);

protected:
	FT_Library m_fontLibrary;

	FontArray m_fonts;
};

