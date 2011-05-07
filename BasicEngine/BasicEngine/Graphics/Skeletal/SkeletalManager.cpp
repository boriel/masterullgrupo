
#include "SkeletalManager.h"
#include "SkeletalCoreModel.h"
#include "SkeletalMesh.h"

//#include "cal3d\cal3d_wrapper.h"
//#include "cal3d\loader.h"



//La función llama al Init por defecto e inicializa Cal3D para que oriente los
//modelos acorde a nuestro sistema de referencia
void cSkeletalManager::Init( unsigned luiMaxSize )
{
	cResourceManager::Init(luiMaxSize);
	
	// Initialize Cal3D Reference System
	CalLoader::setLoadingMode(LOADER_ROTATE_X_AXIS);
}




cResource * cSkeletalManager::LoadResourceInternal( std::string lacNameID, const std::string &lacFile )
{
	cSkeletalCoreModel* lpSkeletalCoreModel = new cSkeletalCoreModel();

	if (!lpSkeletalCoreModel->Init( lacNameID, lacFile ))
	{
		delete lpSkeletalCoreModel;
		return NULL;
	}
	return lpSkeletalCoreModel;
}

cSkeletalMesh * cSkeletalManager::CreateSkeletalMesh(const std::string& lacCoreModelName)
{
	cResourceHandle lHandle = this->FindResource(lacCoreModelName);

	if (lHandle.IsValidHandle())
	{
		cSkeletalCoreModel * lpCoreModel = (cSkeletalCoreModel *)lHandle.GetResource();
		cSkeletalMesh* lpSkeletalMesh = new cSkeletalMesh;
		
		if ( lpSkeletalMesh->Init("", lpCoreModel, 0) )
			return lpSkeletalMesh;
		else
			delete lpSkeletalMesh;
		
	}

	return NULL;
}
