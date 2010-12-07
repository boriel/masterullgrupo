/*
Class FontManager:  NO HACE NADA POR AHORA
*/



#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H


#include "../../Utilities/ResourceManager.h"
#include "../../Utility/Singleton.h"


class cFontManager : public cResourceManager, public cSingleton<cFontManager>
{
	public:
		friend class cSingleton<cFontManager>;
	
	protected:
		cFontManager() { ; } // Protected constructor
	
	private:
		virtual cResource * LoadResourceInternal( std::string lacNameID, const std::string &lacFile );
};





#endif
