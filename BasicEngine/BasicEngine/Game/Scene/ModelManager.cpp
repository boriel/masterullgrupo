#include "ModelManager.h"
#include "Model.h"

#include "..\..\Utility\Resource.h"

cResource* cModelManager::LoadResourceInternal( std::string lacNameID, const std::string &lacFile ) 
{
	cModel* lpModel = new cModel();

	if (!lpModel->Init( lacNameID, lacFile )) 
	{
		delete lpModel;
		return NULL;
	}

	return lpModel;
}
