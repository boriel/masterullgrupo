/*
Class ResourceManager: 			Interfaz para poder acceder al recuro:
				---->Explicación de Jesús<--
				Donde muiNextKey es la clave que se asignará al siguiente recurso que se almacene y
				muiMaxSize es el número máximo de recursos que podemos almacenar en la
				estructura. Como estamos guardando los recursos en un vector, necesitamos una forma
				rápida de saber que casillas del vector están libres para poder almacenar nuevos
				recursos. Es por ello que tenemos una lista adicional que guarda todos los índices de
				casillas que están libres. Por lo tanto, cada vez que añadamos un nuevo elemento,
				sacaremos un índice de la lista de índices libre y lo almacenaremos en esa nueva
				posición con el valor de Key correspondiente a muiNextKey. Justo después de la
				inserción incrementaremos en 1 el valor de muiNextKey.
				
				Si la lista de índices libres está vacía significará que no quedan casillas libres y
				deberemos mostrar un mensaje de error.
				
				Cuando liberemos un recurso, deberemos añadir el índice en el que estaba el recurso
				en la lista de índices libres. De esta forma, la lista siempre nos permitirá acceder a
				casillas libres de forma muy rápida.
			

*/


#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <vector>
#include <list>
#include <string>
#include <tinystr.h>
#include <tinyxml.h>
#include <windows.h>


#include "ResourceHandle.h"
//#include "Resource.h"

class cResource;

//Esta esctructura es lo que se guardará en el vector que contendrá los recursos
struct cInternalResource {
	unsigned int muiKey;			// Clave del recurso
	cResource * mpResource;		// Puntero al recurso
};

class cResourceManager {
public:
	virtual void Init( unsigned luiMaxSize );  //Lo ponemos virtual para poder inicializar la libreria Cal3d de forma adecuada
	void Deinit();

	cResourceHandle LoadResource( std::string lacNameID, const std::string &lacFile ); //una función virtual y será la que implemente cada manager para cargar el recurso específico.
	cResourceHandle LoadResource( std::string lacNameID, void * lpMemoryData, int luiTypeID );

protected:
	std::vector<cInternalResource> maResources;
	std::list<unsigned> mFreeResourceSlot; //lista adicional que guarda todos los índices de casillas que están libres

	int muiNextKey;	//es la clave que se asigna
	unsigned muiMaxSize; //es el número máximo de recursos que podemos almacenar en la estructura

	//La función es protegida y la classe tiene como clase amiga al	handle. Sólo un handle llamar a esta función para acceder al recurso.
	friend class cResourceHandle;	
	cResource* GetResource( cResourceHandle *lpHandle );
			
			
	cResourceHandle AddResourceToPool( cResource * lpResource ); //se encargará de añadir el recurso al vector de recursos
	virtual cResource * LoadResourceInternal( std::string lacNameID, const std::string &lacFile ) { return NULL; };  //carga el recurso desde fichero
	virtual cResource * LoadResourceInternal( std::string lacNameID, void * lpMemoryData, int luiTypeID ) {return NULL;}  //carga el recurso desde memoria

public:
	cResourceHandle FindResource( std::string lacNameID );
	void UnloadResource( cResourceHandle * lpHandle );
	cResourceHandle LoadResourcesXml(std::string lsResource);

private:
	std::string msFilename;  // Resources or Properties file
};

#endif
