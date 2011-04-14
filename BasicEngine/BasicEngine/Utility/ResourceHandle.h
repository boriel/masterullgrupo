/*
class ResourceHandle:
							----->Explicación de los apuntes de Jesús<-------
							El manejador o handle de recursos será una clase que se encargará de permitirnos el
							acceso al recurso en sí. Es importante entender que el resto del código de nuestro juego
							debe almacenar únicamente handles a recursos y no los recursos en sí. Cuando se
							accede a un recurso a través de un handle, debemos hacer uso de él y NUNCA
							guardarnos el puntero al recurso para más tarde.

							El manager de recursos tendrá todos los recursos en un array y el handle contendrá el
							índice del recurso en el array. Esta solución puede plantear un problema de seguridad,
							ya que si el manager decide liberar un recurso y alojar uno nuevo en la misma posición
							que el anterior (lo cual es totalmente válido) todos los handles que apuntaban al
							recurso antiguo y no fueron liberados correctamente estarían apuntando a un recurso
							equivocado sin forma alguna de saberlo.

							Por ello el modelo debe extenderse, por lo que el manager no contendrá el recurso en si
							sino una estructura que llamaremos cInternalResource que contendrá el recurso
							que está almacenado en esa posición y una clave (key). Cada vez que el manager
							almacene un nuevo recurso, le asignará un nuevo valor a la clave, por lo que el handle
							podrá comprobar si el recurso al que accede es el correcto o no.

							La mayor parte de las funciones son getters y setters. Para comprobar si un handle es
							válido se llamará a IsValidHandle (esta función devuelve si el handle es válido, no si el
							recurso está disponible). Para liberar un handle bastará con invalidarlo (llamar a
							Invalidate). Cuando se quiere acceder a un recurso se llamará a GetResource, que
							devolverá NULL si el recurso no está disponible o un puntero al recurso asociado al
							handle. De nuevo recuerden que este puntero debe usarse en el fragmento de código
							en el que estemos y nunca almacenarlo para más tarde.

							Como comprobarán, la llamada a la función Init es protegida, pero la clase
							cResourceManager es una clase amiga. Esto se traduce en que sólo los gestores de
							recursos pueden inicializar un handle.

							Como se fijarán, el handle necesita además un puntero al manager para poder acceder
							al recurso. 
							Como se ve, si la clave es inválida se devuelve directamente NULL. Si la clave por el
							contrario es válida, llamamos a la función GetResource del manager correspondiente
							pasando el handle en sí mismo. Esto se hace sí, ya que el handle contiene toda la
							información necesaria para acceder al recurso. Si las claves no coinciden, será el propio
							manager el que devuelva NULL.
*/


#ifndef RESOURCE_HANDLE_H
#define RESOURCE_HANDLE_H

#include <stdlib.h>

//#include "ResourceManager.h"
//#include "Resource.h"

class cResourceManager;
class cResource;

static const unsigned kuiInvalidKey = 0;


class cResourceHandle
{
	public:
		//variables
		cResource * GetResource();
		
		//Funciones
		cResourceHandle() { mpManager = NULL; muiKey = kuiInvalidKey; }
		
		inline bool IsValidHandle() { return muiKey != kuiInvalidKey; }		// Comprueba si el handle es válido
		inline void Invalidate() { muiKey = kuiInvalidKey; }							// Para invalidar el handle
		inline unsigned GetID() { return muiID; }
		inline unsigned GetKey() { return muiKey; }


	protected:
		friend class cResourceManager;

		void Init( cResourceManager * lpManager, unsigned luiID, unsigned luiKey);

		cResourceManager* mpManager;
		unsigned int muiID;
		unsigned int muiKey;
};



#endif
