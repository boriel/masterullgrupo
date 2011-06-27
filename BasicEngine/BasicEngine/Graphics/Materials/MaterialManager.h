/*
Class MaterialManager.h
*/

#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H


#include "../../Utility/Singleton.h"
#include "../../Utility/Resource.h"
#include "../../Utility/ResourceManager.h"

class cMaterialManager : public cResourceManager, public cSingleton<cMaterialManager> {
public:
	friend class cSingleton<cMaterialManager>;
	cResourceHandle LoadResource( std::string lacNameID, void * lpMemoryData, int liDataType, 
		const std::string &lacMaterialsFile );
	
protected:
	cMaterialManager() { ; } // Protected constructor

private:
	virtual cResource * LoadResourceInternal( std::string lacNameID, void * lpMemoryData, int liDataType );
	cResource * cMaterialManager::LoadResourceInternal( std::string lacNameID, const std::string &lacFile );
};

#endif

