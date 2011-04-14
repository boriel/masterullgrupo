/*
Class TextureManager:

	Lo único que hace es crear una instancia (en el LoadResourceInternal) de cTexture y llama a su función Init con los parámetros asociados. 
	Si la función devuelve error, libera la memoria y devuelve NULL.
	
*/

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H



#include "../../Utility/Singleton.h"
#include "../../Utility/Resource.h"
#include "../../Utility/ResourceManager.h"


class cTextureManager : public cResourceManager, public cSingleton<cTextureManager>
{
	public:
		friend class cSingleton<cTextureManager>;

	protected:
		cTextureManager() { ; } // Protected constructor
	
	private:
		virtual cResource* LoadResourceInternal( std::string lacNameID, const std::string &lacFile );
};



#endif