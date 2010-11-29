/*

#include "Scene.h"

#include <assimp.hpp> // C++ importer interface
#include <aiScene.h> // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>

#include "..\..\Utilities\ResourceHandle.h"


bool cScene::Init( const std::string &lacNameID, const std::string &lacFile )
{
	macFile = lacFile;
	mbLoaded = false;

	// Create an instance of the Importer class
	Assimp::Importer lImporter;

	// Load the scene
	const aiScene* lpScene = lImporter.ReadFile( lacFile.c_str(),
																							aiProcess_CalcTangentSpace |
																							aiProcess_Triangulate |
																							aiProcess_JoinIdenticalVertices |
																							aiProcess_SortByPType);

	// If the import failed, report it
	if( !lpScene )
	{
		printf( lImporter.GetErrorString() );
		return false;
	}

	ProcessScene(lpScene);
	lImporter.FreeScene();
	mbLoaded = true;

	return true;
}


void cScene::Deinit()
{

}


//La clase lpScene cuenta con un atributo llamado mNumMeshes que contiene el
//n�mero de meshes que se encuentran en la escena y un array llamado mMeshes que
//contiene las meshes en s� mismas. Por lo tanto lo que haremos ser� acceder a todas esas
//mallas y cargarlas dentro de una clase cMesh que estar� gestionada por una clase
//cMeshManager que sigue el patr�n de recursos que ya hemos usado con anterioridad
void cScene::ProcessScene( const aiScene* lpScene )
{

	// Meshes
	for (unsigned luiIndex = 0;luiIndex < lpScene->mNumMeshes;++luiIndex)
	{
		char lacMeshName[512];
		sprintf( lacMeshName, "%s_%d", macFile.c_str(), luiIndex);
		cResourceHandle lHandle;
		lHandle = cMeshManager::Get().LoadResource(lacMeshName,	lpScene->mMeshes[luiIndex], 0);
		mMeshList.push_back(lHandle);
	}

}

void cScene::Render()
{
	for ( cMeshHandleListIt lpIt = mMeshList.begin();	lpIt != mMeshList.end(); ++lpIt )
		((cMesh *)lpIt->GetResource())->RenderMesh();
	
}

*/