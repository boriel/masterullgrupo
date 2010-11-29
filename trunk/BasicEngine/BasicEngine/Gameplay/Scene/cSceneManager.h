/*
Class cSceneManager: 

La escena tambi�n har� uso de la estructura de recursos que vimos en el tema anterior.
Por lo tanto tendremos un cSceneManager que heredar� de cResourceManager y una
clase cScene que heredar� de cResource


*/


#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H


#include "../../Utility/ResourceManager.h"
#include "../../Utility/Singleton.h"


class cSceneManager : public cResourceManager, public cSingleton<cSceneManager>
{
	public:
		friend class cSingleton<cSceneManager>;
	
	protected:
		cSceneManager() { ; } // Protected constructor
	
	private:
		virtual cResource * LoadResourceInternal( std::string lacNameID,
		const std::string &lacFile );
};


#endif