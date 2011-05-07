#include "SceneManager.h"
#include "Scene.h"

#include "..\..\Utility\Resource.h"

cResource* cSceneManager::LoadResourceInternal( std::string lacNameID, const std::string &lacFile ) {
	cScene* lpScene = new cScene();

	if (!lpScene->Init( lacNameID, lacFile )) {
		delete lpScene;
		return NULL;
	}

	return lpScene;
}
