#include "MeshManager.h"
#include "Mesh.h"


cResource * cMeshManager::LoadResourceInternal( std::string lacNameID, void * lpMemoryData, int luiTypeID )
{

	if (luiTypeID == kuiStaticMesh)
	{
		cMesh * lpMesh = new cMesh();
	
		if (!lpMesh->Init( lacNameID, lpMemoryData, luiTypeID ))
		{
			delete lpMesh;
			return NULL;
		}

		return lpMesh;
	}
	else if (luiTypeID == kuiSkeletalMesh)
	{
		//cMesh*lpMesh=(cMesh*)cSkeletalManager::Get().CreateSkeletalMesh( (char*)lpMemoryData);
		//return lpMesh;
	}

	return NULL;
}
