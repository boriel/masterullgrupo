/*
class cMeshManager
*/

#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include "../../Utility/ResourceManager.h"
#include "../../Utility/Singleton.h"

class cMeshManager : public cResourceManager, public cSingleton<cMeshManager>
{
	public:
		friend class cSingleton<cMeshManager>;
		void SetScale(float lfScale) { mfScale=lfScale; }

	protected:
	cMeshManager() { mfScale=1.0f; } // Protected constructor
	
	private:
		float mfScale;
		virtual cResource * LoadResourceInternal( std::string lacNameID, void * lpMemoryData,	int luiTypeID );
};

#endif
