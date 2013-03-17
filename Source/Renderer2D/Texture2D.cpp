#include "stdafx.h"
#include "Texture2D.h"

void Texture2D::load(std::string filename)
{
	std::shared_ptr<ResHandle> tex = g_pApp->m_resMan->getHandle(&Resource(filename));
	std::shared_ptr<TextureExtraData> ted = std::static_pointer_cast<TextureExtraData>(tex->getExtra());

	width = ted->width;
	height = ted->height;
	m_ID = ted->texID;
}