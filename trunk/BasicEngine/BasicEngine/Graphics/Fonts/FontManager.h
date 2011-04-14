/*
Class FontManager:  Se encargar� de gestionar las fuentes
*/



#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H


#include "../../Utility/ResourceManager.h"
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
