
#include "MeshManager.h"
#include "Mesh.h"


cResource * cMeshManager::LoadResourceInternal( std::string lacNameID, void * lpMemoryData, int luiTypeID )
{
	cMesh * lpMesh = new cMesh();
	
	if (!lpMesh->Init( lacNameID, lpMemoryData, luiTypeID ))
	{
		delete lpMesh;
		return NULL;
	}

	return lpMesh;
}
