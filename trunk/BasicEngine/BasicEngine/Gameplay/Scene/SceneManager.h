/*
Class cSceneManager: 

La escena también hará uso de la estructura de recursos que vimos en el tema anterior.
Por lo tanto tendremos un cSceneManager que heredará de cResourceManager y una
clase cScene que heredará de cResource

Como pueden comprobar el código es prácticamente igual al ya visto en los ficheros de
código del cTextureManager. La escena vendrá definida por un fichero, crearemos la
escena con ese fichero y si todo ha ido bien, devolveremos la escena recién cargada. De
lo contrario, liberamos la memoria y devolvemos NULL.


*/


/*
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H


#include "../../Utilities/ResourceManager.h"
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

*/