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


//En la función se comprueba si el índice del handle está dentro del rango del array y si
//la casilla correspondiente tiene la misma clave. De ser así, se comprueba si el recurso
//está cargado. Si todo está correcto se devuelve el recurso, de lo contrario se devuelve
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


//Esta función recorre el vector de recursos buscando un recurso que tenga el mismo
//nombre que el que se pasó como parámetro a la función. Si lo encuentra, construye un
//handle y lo devuelve. De lo contrario devuelve un handle inválido.
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


//Si queremos liberar el recurso apuntado por un handle usaríamos la función pública
//Si se encuentra el recurso indicado por el handle, se libera, se limpia la casilla del
//vector y se añade a la lista de índices disponibles el índice de la casilla.
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


//Se encargará de comprobar si el recurso ya se encuentra en el
//vector cargado (imaginemos que dos mallas comparten la misma textura) y de no ser
//así, hacer las llamadas necesarias para cargarlo
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
			lHandle = AddResourceToPool( lpResource );  //Si el recurso se carga correctamente, se añade al vector y se devuelve un handle válido.
		}
		else
			lHandle.Invalidate();
		
	}
	return lHandle;
}


//En la función se extrae el siguiente índice válido, se accede a la posición del array y se
//inicializan sus campos.Después se crea un handle válido que apunte a ese recurso.
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
		if (lElement->Attribute("Fichero") != NULL) //hay name y symbol que estan vacios, y si no pongo esta comprobación da un batacazo el windows!!!
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
