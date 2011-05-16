
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
#include "../../Utility/FileUtils.h"
#include "..\..\MathLib\MathLib.h"

bool cScene::Init( const std::string &lacNameID, const std::string &lacFile ) {
	macFile = lacFile;
	mbLoaded = false;

	// Create an instance of the Importer class
	Assimp::Importer lImporter;

	// Load the scene
	const aiScene* lpScene = lImporter.ReadFile( lacFile.c_str(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType );

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

void cScene::Deinit() { //Destruyendo la memoria
	for (unsigned luiIndex=0; luiIndex < mObjectList.size(); ++luiIndex ) {
		mObjectList[luiIndex]->Deinit();
		delete mObjectList[luiIndex];
	}
}

void cScene::Update( float lfTimestep ) { // Update
	for (unsigned luiIndex=0; luiIndex < mObjectList.size(); ++luiIndex )
		mObjectList[luiIndex]->Update(lfTimestep);
}

void cScene::Render() {//Render
	
	//for ( cMeshHandleListIt lpIt = mMeshList.begin();	lpIt != mMeshList.end(); ++lpIt )
	//	((cMesh *)lpIt->GetResource())->RenderMesh();

	/*
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
	*/

	//Render Objects
	for (unsigned luiIndex=0; luiIndex < mObjectList.size(); ++luiIndex )
		mObjectList[luiIndex]->Render();
	
	
}





//La clase lpScene cuenta con un atributo llamado mNumMeshes que contiene el
//número de meshes que se encuentran en la escena y un array llamado mMeshes que
//contiene las meshes en sí mismas. Por lo tanto lo que haremos será acceder a todas esas
//mallas y cargarlas dentro de una clase cMesh que estará gestionada por una clase
//cMeshManager que sigue el patrón de recursos que ya hemos usado con anterioridad
void cScene::ProcessScene( const aiScene* lpScene )
{
	
	// Meshes
	for (unsigned luiIndex = 0; luiIndex < lpScene->mNumMeshes; ++luiIndex)
	{
		char lacMeshName[512];
		sprintf( lacMeshName, "%s_%d", macFile.c_str(), luiIndex);
		cResourceHandle lHandle;
		lHandle = cMeshManager::Get().LoadResource(lacMeshName,	lpScene->mMeshes[luiIndex], kuiStaticMesh); //De esta forma podemos identificar en el MeshManager que tipo de malla queremos cargar y que tipo de dato recibimos como segundo argumento
		mMeshList.push_back(lHandle);
		
		int liMaterialIndex = lpScene->mMeshes[luiIndex]->mMaterialIndex;
		mMeshMaterialIndexList.push_back(liMaterialIndex);
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

	//Creando los objetos del arbol
	if ( lpScene->mRootNode )
	{
		cMatrix lMatrix;
		lMatrix.LoadIdentity();
		ConvertNodesToObjects( lpScene->mRootNode, lMatrix );
	}

	
}


//Es por ello que nosotros recorreremos el árbol una vez para “aplanar” la jerarquía del árbol,
//calculando sólo una vez las matrices de mundo para cada malla y asumiendo que la
//escena permanecerá estática. La función que nos ayudará a aplanar la jerarquía y a
//crear los objetos es la siguiente función recursiva:
//La función recibe como parámetros el nodo actual que se debe evaluar y la matriz de
//mundo del padre. Al entrar lo primero que se hace es componer la matriz de mundo
//del nodo actual (el código es un poco farragoso, pero simplemente está componiendo
//la matriz creando cuatro vectores de tamaño 4). Después calcula la matriz de mundo
//real acumulando la transformación del padre con la que indicaba el presente nodo.
//A continuación se comprueba si este nodo tiene alguna malla asociada y de ser así, crea
//un nuevo cObject y establece sus datos, para añadir finalmente el objeto a un vector

void cScene::ConvertNodesToObjects( aiNode *lpNode, cMatrix lTransform )
{
	// if node has meshes, create a new scene object for it
	cMatrix lNodeTransform( cVec4(lpNode->mTransformation.a1,
													lpNode->mTransformation.b1,
													lpNode->mTransformation.c1,
													lpNode->mTransformation.d1),
													cVec4(lpNode->mTransformation.a2,
													lpNode->mTransformation.b2,
													lpNode->mTransformation.c2,
													lpNode->mTransformation.d2),
													cVec4(lpNode->mTransformation.a3,
													lpNode->mTransformation.b3,
													lpNode->mTransformation.c3,
													lpNode->mTransformation.d3),
													cVec4(lpNode->mTransformation.a4,
													lpNode->mTransformation.b4,
													lpNode->mTransformation.c4,
													lpNode->mTransformation.d4) );
	
	lTransform = lNodeTransform * lTransform;

	if( lpNode->mNumMeshes > 0)
	{
		cObject *lpObject = new cObject;
		lpObject->Init();
		lpObject->SetName( lpNode->mName.data );
		lpObject->SetWorldMatrix(lTransform);

		for (unsigned luiIndex=0;luiIndex<lpNode->mNumMeshes;++luiIndex)
		{
			unsigned luiMeshIndex = lpNode->mMeshes[luiIndex];
			unsigned luiMaterialIndex;
			luiMaterialIndex = mMeshMaterialIndexList[luiMeshIndex];
			lpObject->AddMesh( mMeshList[luiMeshIndex],
			mMaterialList[luiMaterialIndex] );
		}

	mObjectList.push_back(lpObject);
	}

	// continue for all child nodes
	for(unsigned luiIndex = 0;luiIndex<lpNode->mNumChildren;++luiIndex)
		ConvertNodesToObjects( lpNode->mChildren[luiIndex], lTransform);
	

}
