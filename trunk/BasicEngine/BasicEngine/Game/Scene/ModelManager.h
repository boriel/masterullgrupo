/*
Class cSceneManager: 

La escena tambi�n har� uso de la estructura de recursos que vimos en el tema anterior.
Por lo tanto tendremos un cSceneManager que heredar� de cResourceManager y una
clase cScene que heredar� de cResource

Como pueden comprobar el c�digo es pr�cticamente igual al ya visto en los ficheros de
c�digo del cTextureManager. La escena vendr� definida por un fichero, crearemos la
escena con ese fichero y si todo ha ido bien, devolveremos la escena reci�n cargada. De
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

