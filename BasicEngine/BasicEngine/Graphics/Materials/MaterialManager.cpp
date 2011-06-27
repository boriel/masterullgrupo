/* File: MaterialManager.cpp */
#include "MaterialManager.h"
#include "Material.h"

cResource * cMaterialManager::LoadResourceInternal( std::string lacNameID, void * lpMemoryData, int liDataType ) 
{
	cMaterial * lpMaterial = new cMaterial();
	lpMaterial->Init( lacNameID, lpMemoryData, liDataType );
	return lpMaterial;
}


cResource * cMaterialManager::LoadResourceInternal( std::string lacNameID, const std::string &lacFile )
{
	cMaterial * lpMaterial = new cMaterial();

	if (!lpMaterial->Init( lacNameID, lacFile ))
	{
		delete lpMaterial;
		return NULL;
	}

	return lpMaterial;
}



cResourceHandle cMaterialManager::LoadResource( std::string lacNameID, void * lpMemoryData, int liDataType, 
		const std::string &lacMaterialsFile )
{
	cResourceHandle lHandle = FindResource( lacNameID );
	if ( !lHandle.IsValidHandle() )
	{
		// Load the Resource
		cMaterial * lpMaterial = new cMaterial();
		lpMaterial->Init( lacNameID, lpMemoryData, liDataType, lacMaterialsFile);

		if (lpMaterial)
		{
			// Set the ID
			lpMaterial->SetNameID( lacNameID );

			// Save it into the pool
			lHandle = AddResourceToPool( lpMaterial );
		}
		else
			lHandle.Invalidate();
	}

	return lHandle;
}
