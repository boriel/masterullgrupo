

#include "Scene.h"

#include <assimp.hpp> // C++ importer interface
#include <aiScene.h> // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>


#include "SceneManager.h"
#include "..\..\Graphics\Meshes\MeshManager.h"
#include "..\..\Graphics\Meshes\Mesh.h"
#include "../../Graphics/Materials/MaterialData.h"
#include "../../Graphics/Materials/Material.h"
#include "../../Graphics/Materials/MaterialManager.h"
#include "../../Utilities/FileUtils.h"

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
//número de meshes que se encuentran en la escena y un array llamado mMeshes que
//contiene las meshes en sí mismas. Por lo tanto lo que haremos será acceder a todas esas
//mallas y cargarlas dentro de una clase cMesh que estará gestionada por una clase
//cMeshManager que sigue el patrón de recursos que ya hemos usado con anterioridad
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
	

	
	// Materials
	assert(lpScene->HasMaterials());
	for (unsigned luiIndex = 0;luiIndex<lpScene->mNumMaterials;++luiIndex)
	{
		// Access the material name
		aiString lName;
		lpScene->mMaterials[luiIndex]->Get(AI_MATKEY_NAME, lName);

		// Fill in the material data structure
		cMaterialData lMaterialData;
		lMaterialData.macPath = cFileUtils::GetDirectory(macFile);
		lMaterialData.mpMaterial = lpScene->mMaterials[luiIndex];

		// Load the resource
		cResourceHandle lHandle;
		lHandle = cMaterialManager::Get().LoadResource(lName.data, &lMaterialData, 0);

		// Save the material on a vector in the Scene
		mMaterialList.push_back(lHandle);
		int liMaterialIndex = lpScene->mMeshes[luiIndex]->mMaterialIndex;
		mMeshMaterialIndexList.push_back(liMaterialIndex);
	
	}
	
	


}

void cScene::Render()
{
	
	//for ( cMeshHandleListIt lpIt = mMeshList.begin();	lpIt != mMeshList.end(); ++lpIt )
	//	((cMesh *)lpIt->GetResource())->RenderMesh();

	for ( cResourceHandleListIt lpIt = mMeshList.begin();	lpIt != mMeshList.end(); ++lpIt )
		((cMesh*)lpIt->GetResource())->RenderMesh();

	
	for (unsigned luiIndex = 0; luiIndex < mMeshList.size();++luiIndex)
	{
		// Get material index
		unsigned luiMaterialIndex = mMeshMaterialIndexList[luiIndex];

		// Set the material
		void * lpResource = mMaterialList[luiMaterialIndex].GetResource();
		((cMaterial *)lpResource)->SetMaterial();

		// Render Mesh
		lpResource = mMeshList[luiIndex].GetResource();
		((cMesh *)lpResource)->RenderMesh();
	}
	


}

