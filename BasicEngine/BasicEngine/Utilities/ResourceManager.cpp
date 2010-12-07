#include "ResourceManager.h"

#include <cassert>
#include <stdio.h>


#include "Resource.h"

#include "..\Graphics\Fonts\acgfx_font.h"

void cResourceManager::Init( unsigned luiMaxSize )
{
	muiMaxSize = luiMaxSize;
	
	// Initialize the structures
	maResources.resize( muiMaxSize );
	mFreeResourceSlot.clear();
	
	for ( unsigned luiIndex = 0; luiIndex < muiMaxSize; ++luiIndex )
	{
		// Initialize the resource slot
		maResources[luiIndex].muiKey = kuiInvalidKey;
		maResources[luiIndex].mpResource = NULL;

		// Add the free index to the list
		mFreeResourceSlot.push_back( luiIndex );
	}

	// Prepare the first key
	muiNextKey = kuiInvalidKey + 1;


	//incializando el nombre del fichero de recursos del nombre del xml
	msFilename = (".\\Data\\" + std::string("Resources.xml"));

	LoadResourcesXml(msFilename.c_str());

}


void cResourceManager::Deinit()
{
	for ( unsigned luiIndex = 0; luiIndex < muiMaxSize; ++luiIndex )
	{
		// Is a valid resource?
		if ( maResources[luiIndex].muiKey != kuiInvalidKey )
		{
			// Check that all is right
			assert( maResources[luiIndex].mpResource );
			assert( maResources[luiIndex].mpResource->IsLoaded() );

			// Deinit the resource
			maResources[luiIndex].mpResource->Deinit();
			delete maResources[luiIndex].mpResource;

			// Clear the resource slot
			maResources[luiIndex].muiKey = kuiInvalidKey;
			maResources[luiIndex].mpResource = NULL;
		}
	}
}


//En la funci�n se comprueba si el �ndice del handle est� dentro del rango del array y si
//la casilla correspondiente tiene la misma clave. De ser as�, se comprueba si el recurso
//est� cargado. Si todo est� correcto se devuelve el recurso, de lo contrario se devuelve
//NULL.
cResource * cResourceManager::GetResource( cResourceHandle *lpHandle )
{
	assert( lpHandle );
	assert( lpHandle->IsValidHandle() );
	
	unsigned luiIndex = lpHandle->GetID();
	assert( luiIndex < muiMaxSize );
	
	if ( maResources[luiIndex].muiKey == lpHandle->GetKey()	&& maResources[luiIndex].mpResource->IsLoaded() )
		return maResources[luiIndex].mpResource;
	
	return NULL;
}


//Esta funci�n recorre el vector de recursos buscando un recurso que tenga el mismo
//nombre que el que se pas� como par�metro a la funci�n. Si lo encuentra, construye un
//handle y lo devuelve. De lo contrario devuelve un handle inv�lido.
cResourceHandle cResourceManager::FindResource( std::string lacNameID )
{
	cResourceHandle lHandle;

	for ( unsigned luiIndex = 0; luiIndex < muiMaxSize; ++luiIndex )
	{
			// Is a valid resource?
		if ( maResources[luiIndex].muiKey != kuiInvalidKey )
		{
			// Check that all is right
			assert( maResources[luiIndex].mpResource );
			assert( maResources[luiIndex].mpResource->IsLoaded() );

			// Is the right resource?
			if ( maResources[luiIndex].mpResource->IsThisResource( lacNameID ) )
			{
				lHandle.Init(this, luiIndex, maResources[luiIndex].muiKey);
				break;
			}
		}
	}

	return lHandle;
}


//Si queremos liberar el recurso apuntado por un handle usar�amos la funci�n p�blica
//Si se encuentra el recurso indicado por el handle, se libera, se limpia la casilla del
//vector y se a�ade a la lista de �ndices disponibles el �ndice de la casilla.
void cResourceManager::UnloadResource( cResourceHandle * lpHandle )
{
	assert( lpHandle );
	assert( lpHandle->IsValidHandle() );

	unsigned luiIndex = lpHandle->GetID();

	assert( luiIndex < muiMaxSize );

	if ( maResources[luiIndex].muiKey == lpHandle->GetKey()	&& maResources[luiIndex].mpResource->IsLoaded() )
	{
		// Deinit the resource
		maResources[luiIndex].mpResource->Deinit();
		delete maResources[luiIndex].mpResource;

		// Clear the resource slot
		maResources[luiIndex].muiKey = kuiInvalidKey;
		maResources[luiIndex].mpResource = NULL;

		// Add the slot to the free list
		mFreeResourceSlot.push_front(luiIndex);
	}
}


//Se encargar� de comprobar si el recurso ya se encuentra en el
//vector cargado (imaginemos que dos mallas comparten la misma textura) y de no ser
//as�, hacer las llamadas necesarias para cargarlo
cResourceHandle cResourceManager::LoadResource( std::string lacNameID, const std::string &lacFile )
{
	cResourceHandle lHandle = FindResource( lacNameID );
	if ( !lHandle.IsValidHandle() )
	{
		// Load the Resource
		cResource * lpResource = LoadResourceInternal( lacNameID,	lacFile );
		
		if (lpResource)
		{
			// Set the ID
			lpResource->SetNameID( lacNameID );

			// Save it into the pool
			lHandle = AddResourceToPool( lpResource );  //Si el recurso se carga correctamente, se a�ade al vector y se devuelve un handle v�lido.
		}
		else
			lHandle.Invalidate();
		
	}
	return lHandle;
}


//En la funci�n se extrae el siguiente �ndice v�lido, se accede a la posici�n del array y se
//inicializan sus campos.Despu�s se crea un handle v�lido que apunte a ese recurso.
cResourceHandle cResourceManager::AddResourceToPool( cResource * lpResource )
{
	assert( mFreeResourceSlot.size() > 0 );
	
	unsigned luiNext = *mFreeResourceSlot.begin();
	mFreeResourceSlot.pop_front();
	
	assert( maResources[luiNext].muiKey == kuiInvalidKey );
	assert(muiNextKey != kuiInvalidKey );
	
	maResources[luiNext].muiKey = muiNextKey++;
	maResources[luiNext].mpResource = lpResource;
	
	cResourceHandle lHandle;
	
	lHandle.Init(this, luiNext, maResources[luiNext].muiKey);
	return lHandle;
}


//Cargando el recurso desde memoria
cResourceHandle cResourceManager::LoadResource( std::string lacNameID, void * lpMemoryData, int luiTypeID )
{
	cResourceHandle lHandle = FindResource( lacNameID );
	if ( !lHandle.IsValidHandle() )
	{
		// Load the Resource
		cResource * lpResource = LoadResourceInternal( lacNameID,	lpMemoryData, luiTypeID );

		if (lpResource)
		{
			// Set the ID
			lpResource->SetNameID( lacNameID );

			// Save it into the pool
			lHandle = AddResourceToPool( lpResource );
		}
		else
			lHandle.Invalidate();
	}

	return lHandle;
}


//Leemeos todos los recursos desde un xml
bool cResourceManager::LoadResourcesXml(std::string lsResource)
{

	/*
	mDoc.LoadFile ((char*)msFilename.c_str());
	if (!mDoc.LoadFile())
	{
		OutputDebugString ("XML Load: FAILED\n");
		return false;
	}

	
	TiXmlElement *lElement;
	lElement = mDoc.FirstChildElement (lsTag);

	if (lsTag == "Font")
	{
		if (lElement->Attribute("Fichero") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobaci�n da un batacazo el windows!!!
			std::string lsFont = ((char*)lElement->Attribute("Fichero"));
		else
			return false;



	}
	*/

	//std::string lacFont = "./Data/Fonts/Test1.fnt";
	//cFont lFont;
	//lFont.Init(lacFont.c_str());
	
	//LoadResource("Font", &lFont, 10);
	

	//LoadResource("Font2", "./Data/Fonts/Test1_0.tga");
	//LoadResource("Font3", ".\\Data\\Fonts\\Test1_0.tga");
	
	
	//LoadResource("Font1", "./Data/Fonts/Test1.fnt");

	//LoadResource("Font2", ".\\Data\\Fonts\\Test2.fnt");

	maResources;

	return true;
	
}
