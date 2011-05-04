/*
Class ResourceManager: 			Interfaz para poder acceder al recuro:
				---->Explicaci�n de Jes�s<--
				Donde muiNextKey es la clave que se asignar� al siguiente recurso que se almacene y
				muiMaxSize es el n�mero m�ximo de recursos que podemos almacenar en la
				estructura. Como estamos guardando los recursos en un vector, necesitamos una forma
				r�pida de saber que casillas del vector est�n libres para poder almacenar nuevos
				recursos. Es por ello que tenemos una lista adicional que guarda todos los �ndices de
				casillas que est�n libres. Por lo tanto, cada vez que a�adamos un nuevo elemento,
				sacaremos un �ndice de la lista de �ndices libre y lo almacenaremos en esa nueva
				posici�n con el valor de Key correspondiente a muiNextKey. Justo despu�s de la
				inserci�n incrementaremos en 1 el valor de muiNextKey.
				
				Si la lista de �ndices libres est� vac�a significar� que no quedan casillas libres y
				deberemos mostrar un mensaje de error.
				
				Cuando liberemos un recurso, deberemos a�adir el �ndice en el que estaba el recurso
				en la lista de �ndices libres. De esta forma, la lista siempre nos permitir� acceder a
				casillas libres de forma muy r�pida.
			

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

//Esta esctructura es lo que se guardar� en el vector que contendr� los recursos
struct cInternalResource {
	unsigned int muiKey;			// Clave del recurso
	cResource * mpResource;		// Puntero al recurso
};

class cResourceManager {
public:
	virtual void Init( unsigned luiMaxSize );  //Lo ponemos virtual para poder inicializar la libreria Cal3d de forma adecuada
	void Deinit();

	cResourceHandle LoadResource( std::string lacNameID, const std::string &lacFile ); //una funci�n virtual y ser� la que implemente cada manager para cargar el recurso espec�fico.
	cResourceHandle LoadResource( std::string lacNameID, void * lpMemoryData, int luiTypeID );

protected:
	std::vector<cInternalResource> maResources;
	std::list<unsigned> mFreeResourceSlot; //lista adicional que guarda todos los �ndices de casillas que est�n libres

	int muiNextKey;	//es la clave que se asigna
	unsigned muiMaxSize; //es el n�mero m�ximo de recursos que podemos almacenar en la estructura

	//La funci�n es protegida y la classe tiene como clase amiga al	handle. S�lo un handle llamar a esta funci�n para acceder al recurso.
	friend class cResourceHandle;	
	cResource* GetResource( cResourceHandle *lpHandle );
			
			
	cResourceHandle AddResourceToPool( cResource * lpResource ); //se encargar� de a�adir el recurso al vector de recursos
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
