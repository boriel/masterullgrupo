/*
class ResourceHandle:
							----->Explicaci�n de los apuntes de Jes�s<-------
							El manejador o handle de recursos ser� una clase que se encargar� de permitirnos el
							acceso al recurso en s�. Es importante entender que el resto del c�digo de nuestro juego
							debe almacenar �nicamente handles a recursos y no los recursos en s�. Cuando se
							accede a un recurso a trav�s de un handle, debemos hacer uso de �l y NUNCA
							guardarnos el puntero al recurso para m�s tarde.

							El manager de recursos tendr� todos los recursos en un array y el handle contendr� el
							�ndice del recurso en el array. Esta soluci�n puede plantear un problema de seguridad,
							ya que si el manager decide liberar un recurso y alojar uno nuevo en la misma posici�n
							que el anterior (lo cual es totalmente v�lido) todos los handles que apuntaban al
							recurso antiguo y no fueron liberados correctamente estar�an apuntando a un recurso
							equivocado sin forma alguna de saberlo.

							Por ello el modelo debe extenderse, por lo que el manager no contendr� el recurso en si
							sino una estructura que llamaremos cInternalResource que contendr� el recurso
							que est� almacenado en esa posici�n y una clave (key). Cada vez que el manager
							almacene un nuevo recurso, le asignar� un nuevo valor a la clave, por lo que el handle
							podr� comprobar si el recurso al que accede es el correcto o no.

							La mayor parte de las funciones son getters y setters. Para comprobar si un handle es
							v�lido se llamar� a IsValidHandle (esta funci�n devuelve si el handle es v�lido, no si el
							recurso est� disponible). Para liberar un handle bastar� con invalidarlo (llamar a
							Invalidate). Cuando se quiere acceder a un recurso se llamar� a GetResource, que
							devolver� NULL si el recurso no est� disponible o un puntero al recurso asociado al
							handle. De nuevo recuerden que este puntero debe usarse en el fragmento de c�digo
							en el que estemos y nunca almacenarlo para m�s tarde.

							Como comprobar�n, la llamada a la funci�n Init es protegida, pero la clase
							cResourceManager es una clase amiga. Esto se traduce en que s�lo los gestores de
							recursos pueden inicializar un handle.

							Como se fijar�n, el handle necesita adem�s un puntero al manager para poder acceder
							al recurso. 
							Como se ve, si la clave es inv�lida se devuelve directamente NULL. Si la clave por el
							contrario es v�lida, llamamos a la funci�n GetResource del manager correspondiente
							pasando el handle en s� mismo. Esto se hace s�, ya que el handle contiene toda la
							informaci�n necesaria para acceder al recurso. Si las claves no coinciden, ser� el propio
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
		
		inline bool IsValidHandle() { return muiKey != kuiInvalidKey; }		// Comprueba si el handle es v�lido
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
