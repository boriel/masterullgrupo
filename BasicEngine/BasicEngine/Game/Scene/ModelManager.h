/*
Class cSceneManager: 

La escena también hará uso de la estructura de recursos que vimos en el tema anterior.
Por lo tanto tendremos un cSceneManager que heredará de cResourceManager y una
clase cScene que heredará de cResource

Como pueden comprobar el código es prácticamente igual al ya visto en los ficheros de
código del cTextureManager. La escena vendrá definida por un fichero, crearemos la
escena con ese fichero y si todo ha ido bien, devolveremos la escena recién cargada. De
lo contrario, liberamos la memoria y devolvemos NULL.


clase cambiada: ModelManager: Se encarga de cargar y gestionar los modelos cargados
*/

#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "../../Utility/ResourceManager.h"
#include "../../Utility/Singleton.h"


class cModelManager : public cResourceManager, public cSingleton<cModelManager> {
	public:
		friend class cSingleton<cModelManager>;
	
	protected:
		cModelManager() { ; } // Protected constructor
	
	private:
		virtual cResource * LoadResourceInternal( std::string lacNameID, const std::string &lacFile );
};


#endif

