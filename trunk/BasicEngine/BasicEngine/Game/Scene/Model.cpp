
#include "Model.h"

#include "ModelManager.h"
#include "..\..\Graphics\Meshes\MeshManager.h"
#include "..\..\Graphics\Meshes\Mesh.h"
#include "..\..\Graphics\Materials/MaterialData.h"
#include "..\..\Graphics\Materials/Material.h"
#include "..\..\Graphics\Materials/MaterialManager.h"
#include "..\..\Utility\FileUtils.h"
#include "..\..\MathLib\MathLib.h"
#include "..\..\Graphics\GraphicManager.h"
#include "..\Object\ObjectManager.h"

#include "..\..\Physics\Objects\PhysicsPista.h"

#include <assimp.hpp> // C++ importer interface
#include <aiScene.h> // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>
#include <iostream>

bool cModel::Init( const std::string &lacNameID, const std::string &lacFile ) 
{
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

//Destruyendo la memoria
void cModel::Deinit() 
{ 
	for (unsigned luiIndex=0; luiIndex < mSubModelList.size(); ++luiIndex ) 
	{
		mSubModelList[luiIndex]->Deinit();
		delete mSubModelList[luiIndex];
	}
}

//Update
void cModel::Update( float lfTimestep ) 
{ 
	for (unsigned luiIndex=0; luiIndex < mSubModelList.size(); ++luiIndex )
		mSubModelList[luiIndex]->Update(lfTimestep);
}

//Render
//void cModel::Render() 
void cModel::Render(cMatrix &lWorld) 
{
	
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

	/*
	//Render Objects
	for (unsigned luiIndex = 0; luiIndex < mObjectList.size(); ++luiIndex )
		mObjectList[luiIndex]->Render();
	*/

	for (unsigned luiIndex = 0; luiIndex < mSubModelList.size(); ++luiIndex )
		mSubModelList[luiIndex]->Render(lWorld);
}


//La clase lpScene cuenta con un atributo llamado mNumMeshes que contiene el
//número de meshes que se encuentran en la escena y un array llamado mMeshes que
//contiene las meshes en sí mismas. Por lo tanto lo que haremos será acceder a todas esas
//mallas y cargarlas dentro de una clase cMesh que estará gestionada por una clase
//cMeshManager que sigue el patrón de recursos que ya hemos usado con anterioridad
void cModel::ProcessScene( const aiScene* lpScene )
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
	for (unsigned luiIndex = 0; luiIndex<lpScene->mNumMaterials; ++luiIndex)
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

	ProcessBounding(); //Calcular el bounding del modelo
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

void cModel::ConvertNodesToObjects( aiNode *lpNode, cMatrix lTransform )
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
		cSubModel *lpSubModel = new cSubModel;
		lpSubModel->Init();
		lpSubModel->SetName( lpNode->mName.data );
		lpSubModel->SetLocalMatrix(lTransform);

		for (unsigned luiIndex=0;luiIndex<lpNode->mNumMeshes;++luiIndex)
		{
			unsigned luiMeshIndex = lpNode->mMeshes[luiIndex];
			unsigned luiMaterialIndex;
			luiMaterialIndex = mMeshMaterialIndexList[luiMeshIndex];
			lpSubModel->AddMesh( mMeshList[luiMeshIndex],
			mMaterialList[luiMaterialIndex] );
		}

	mSubModelList.push_back(lpSubModel);
	}

	// continue for all child nodes
	for(unsigned luiIndex = 0;luiIndex<lpNode->mNumChildren;++luiIndex)
		ConvertNodesToObjects( lpNode->mChildren[luiIndex], lTransform);
}


//tBounding cModel::ProcessBounding() 
void cModel::ProcessBounding() 
{
#ifdef _DEBUG
	cout << " " << endl;
	cout << "[BOUNDING] File: " << macFile << endl;
	cout << "* NumMeshes = " <<  mMeshList.size() <<endl;
#endif

	for(unsigned int luiMeshIndex=0; luiMeshIndex<mMeshList.size(); luiMeshIndex++) {
		cMesh* lpMesh = (cMesh*) mMeshList[luiMeshIndex].GetResource();
#ifdef _DEBUG
		cout << "  + Mesh["<<luiMeshIndex<<"].NumVertext = "<<lpMesh->muiNumVertex<<endl;
#endif
		tBounding lBounding;
		lBounding.mvCenter=cVec3(0,0,0);
		lBounding.mvMax=cVec3(0,0,0);
		lBounding.mvMin=cVec3(0,0,0);
		float lfX, lfY, lfZ;

		for(unsigned int luiVertexIndex=0; luiVertexIndex<(lpMesh->muiNumVertex); luiVertexIndex++) {//Process bounding mesh
			cVec3* lpVertex = lpMesh->mpVertexPositionBuffer; 
			lfX = lpVertex[luiVertexIndex].x;
			lfY = lpVertex[luiVertexIndex].y;
			lfZ = lpVertex[luiVertexIndex].z;

			if (lfX>lBounding.mvMax.x) lBounding.mvMax.x = lfX;
			if (lfY>lBounding.mvMax.y) lBounding.mvMax.y = lfY;
			if (lfZ>lBounding.mvMax.z) lBounding.mvMax.z = lfZ;
			if (lfX<lBounding.mvMin.x) lBounding.mvMin.x = lfX;
 			if (lfY<lBounding.mvMin.y) lBounding.mvMin.y = lfY;
			if (lfZ<lBounding.mvMin.z) lBounding.mvMax.z = lfZ;
		}
		lBounding.mvCenter.x=(lBounding.mvMax.x-abs(lBounding.mvMin.x))/2;
		lBounding.mvCenter.y=(lBounding.mvMax.y-abs(lBounding.mvMin.y))/2;
		lBounding.mvCenter.z=(lBounding.mvMax.z-abs(lBounding.mvMin.z))/2;
		lBounding.mfRadius=lBounding.mvCenter.DistanceTo(lBounding.mvMin);	//Calculate radius

#ifdef _DEBUG
		cout << "    > Bounding X:{"<<lBounding.mvMin.x<<", "<<lBounding.mvMax.x;
		cout << "} Y:{"<<lBounding.mvMin.y<<", "<<lBounding.mvMax.y;
		cout << "} Z:{"<<lBounding.mvMin.z<<", "<<lBounding.mvMax.z<<"}";
		cout <<", Centro("<<lBounding.mvCenter.x<<", "<<lBounding.mvCenter.y<<", "<<lBounding.mvCenter.z<<")";
		cout << ", Radio="<<lBounding.mfRadius<<endl;
#endif
	}

	
}

/*
void cModel::ProcessBoundingFile(string lacFile) { 
	Assimp::Importer lImporter; // Create an instance of the Importer class
	
	// Load the scene
	const aiScene* lpScene = lImporter.ReadFile( lacFile.c_str(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType );

	if( !lpScene ) { // If the import failed, report it
		cout << "[ERROR] Model.ShowInfo: " << lImporter.GetErrorString() << endl;;
		return;
	}
	ProcessBoundingScene(lpScene,macFile);
}*/

/*
void cModel::ProcessBoundingScene(const aiScene* lpScene, string lacFile) {
#ifdef _DEBUG
	cout << " " << endl;
	cout << "[INFO] Model.ShowInfo: " << lacFile << endl;
	cout << "{ NumChildren=" << lpScene->mRootNode->mNumChildren << ", ";
	cout << " NumMeshes=" << lpScene->mRootNode->mNumMeshes << ", ";
	cout << " NumVertices[Mesh=0]=" << lpScene->mMeshes[0]->mNumVertices << "}"<<endl;
#endif

	ProcessBoundingMesh(lpScene->mMeshes[0]); //FIXME: de momento sólo calculamos el bounding global

#ifdef _DEBUG
	for (unsigned int luiNodeIndex=0; luiNodeIndex<lpScene->mRootNode->mNumChildren; luiNodeIndex++) 
	{
		const aiNode *lpNode = lpScene->mRootNode->mChildren[luiNodeIndex];
		cout << "* Node Children["<< luiNodeIndex << "]=" << (lpNode->mName.data);
		cout << " (mNumMeshes=" << lpNode->mNumMeshes << ")"<<endl;

		//FIXME: Revisar cómo identificar los vértices de cada Malla y luego 
		//procesar cada malla para obtener los bounding de cada una
//		for (unsigned int luiMeshIndex=0; luiMeshIndex<lpNode->mNumMeshes;luiMeshIndex++)
//		{
//			ShowInfoMesh((aiMesh*) lpNode->mMeshes[luiMeshIndex]);
//		}

	}
#endif
}*/

/*
void cModel::ProcessBoundingMesh(aiMesh* lpMesh) {
	mBounding.mvCenter=cVec3(0,0,0);
	mBounding.mvMax=cVec3(0,0,0);
	mBounding.mvMin=cVec3(0,0,0);

	float lfX, lfY, lfZ;
	
	for (unsigned int luiIndex=0; luiIndex<(lpMesh->mNumVertices); luiIndex++) {
		lfX = lpMesh->mVertices[luiIndex].x;
		lfY = lpMesh->mVertices[luiIndex].y;
		lfZ = lpMesh->mVertices[luiIndex].z;
		if (lfX>mBounding.mvMax.x) mBounding.mvMax.x = lfX;
		if (lfY>mBounding.mvMax.y) mBounding.mvMax.y = lfY;
		if (lfZ>mBounding.mvMax.z) mBounding.mvMax.z = lfZ;
		if (lfX<mBounding.mvMin.x) mBounding.mvMin.x = lfX;
 		if (lfY<mBounding.mvMin.y) mBounding.mvMin.y = lfY;
		if (lfZ<mBounding.mvMin.z) mBounding.mvMax.z = lfZ;
	}
	mBounding.mvCenter.x=(mBounding.mvMax.x-abs(mBounding.mvMin.x))/2;
	mBounding.mvCenter.y=(mBounding.mvMax.y-abs(mBounding.mvMin.y))/2;
	mBounding.mvCenter.z=(mBounding.mvMax.z-abs(mBounding.mvMin.z))/2;
	mBounding.mfRadius=mBounding.mvCenter.DistanceTo(mBounding.mvMin);	//Calculate radius

#ifdef _DEBUG
	cout << " > Bounding Box"<<endl;
	cout << "   - X:{"<<mBounding.mvMin.x<<", "<<mBounding.mvMax.x;
	cout << "} Y:{"<<mBounding.mvMin.y<<", "<<mBounding.mvMax.y;
	cout << "} Z:{"<<mBounding.mvMin.z<<", "<<mBounding.mvMax.z<<"}"<<endl;
	cout <<"   - Centro ("<<mBounding.mvCenter.x<<", "<<mBounding.mvCenter.y<<", "<<mBounding.mvCenter.z<<") "<<endl;
	cout << "   - Radio esfera = "<<mBounding.mfRadius<<endl;
#endif
}*/

/*
//Obtenemos el Box de una Mesh
void cModel::GetBox() 
{
#ifdef _DEBUG
	cout << " " << endl;
	cout << "[BOUNDING] File: " << macFile << endl;
	cout << "* NumMeshes = " <<  mMeshList.size() <<endl;
#endif

	for(unsigned int luiMeshIndex=0; luiMeshIndex<mMeshList.size(); luiMeshIndex++) {
		cMesh* lpMesh = (cMesh*) mMeshList[luiMeshIndex].GetResource();
#ifdef _DEBUG
		cout << "  + Mesh["<<luiMeshIndex<<"].NumVertext = "<<lpMesh->muiNumVertex<<endl;
#endif
		tBounding lBounding;
		lBounding.mvCenter=cVec3(0,0,0);
		lBounding.mvMax=cVec3(0,0,0);
		lBounding.mvMin=cVec3(0,0,0);
		float lfX, lfY, lfZ;

		for(unsigned int luiVertexIndex=0; luiVertexIndex<(lpMesh->muiNumVertex); luiVertexIndex++) {//Process bounding mesh
			cVec3* lpVertex = lpMesh->mpVertexPositionBuffer; 
			lfX = lpVertex[luiVertexIndex].x;
			lfY = lpVertex[luiVertexIndex].y;
			lfZ = lpVertex[luiVertexIndex].z;

			if (lfX>lBounding.mvMax.x) lBounding.mvMax.x = lfX;
			if (lfY>lBounding.mvMax.y) lBounding.mvMax.y = lfY;
			if (lfZ>lBounding.mvMax.z) lBounding.mvMax.z = lfZ;
			if (lfX<lBounding.mvMin.x) lBounding.mvMin.x = lfX;
 			if (lfY<lBounding.mvMin.y) lBounding.mvMin.y = lfY;
			if (lfZ<lBounding.mvMin.z) lBounding.mvMax.z = lfZ;
		}
		lBounding.mvCenter.x=(lBounding.mvMax.x-abs(lBounding.mvMin.x))/2;
		lBounding.mvCenter.y=(lBounding.mvMax.y-abs(lBounding.mvMin.y))/2;
		lBounding.mvCenter.z=(lBounding.mvMax.z-abs(lBounding.mvMin.z))/2;
		lBounding.mfRadius=lBounding.mvCenter.DistanceTo(lBounding.mvMin);	//Calculate radius

#ifdef _DEBUG
		cout << "    > Bounding X:{"<<lBounding.mvMin.x<<", "<<lBounding.mvMax.x;
		cout << "} Y:{"<<lBounding.mvMin.y<<", "<<lBounding.mvMax.y;
		cout << "} Z:{"<<lBounding.mvMin.z<<", "<<lBounding.mvMax.z<<"}";
		cout <<", Centro("<<lBounding.mvCenter.x<<", "<<lBounding.mvCenter.y<<", "<<lBounding.mvCenter.z<<")";
		cout << ", Radio="<<lBounding.mfRadius<<endl;
#endif
	}

	
}
*/