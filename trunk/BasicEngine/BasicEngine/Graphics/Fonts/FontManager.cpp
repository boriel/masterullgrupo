#include "FontManager.h"

#include "acgfx_font.h"

#include "..\..\Utilities\Resource.h"

cResource* cFontManager::LoadResourceInternal( std::string lacNameID, const std::string &lacFile )
{
	cFont* lpFont = new cFont();

	//if (!lpFont->Init( lacNameID, lacFile ))
	if (!lpFont->Init( lacFile.c_str()))
	{
		delete lpFont;
		return NULL;
	}

	return lpFont;
}
