
#include "Model.h"

#include "ModelManager.h"
#include "..\..\Graphics\Meshes\MeshManager.h"
#include "..\..\Graphics\Meshes\Mesh.h"
#include "../../Graphics/Materials/MaterialData.h"
#include "../../Graphics/Materials/Material.h"
#include "../../Graphics/Materials/MaterialManager.h"
#include "../../Utility/FileUtils.h"
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
	for (unsigned luiIndex=0; luiIndex < mObjectList.size(); ++luiIndex ) 
	{
		mObjectList[luiIndex]->Deinit();
		delete mObjectList[luiIndex];
	}
}

//Update
void cModel::Update( float lfTimestep ) 
{ 
	for (unsigned luiIndex=0; luiIndex < mObjectList.size(); ++luiIndex )
		mObjectList[luiIndex]->Update(lfTimestep);
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


	for (unsigned luiIndex = 0; luiIndex < mObjectList.size(); ++luiIndex )
		mObjectList[luiIndex]->Render(lWorld);


}





//La clase lpScene cuenta con un atributo llamado mNumMeshes que contiene el
//n�mero de meshes que se encuentran en la escena y un array llamado mMeshes que
//contiene las meshes en s� mismas. Por lo tanto lo que haremos ser� acceder a todas esas
//mallas y cargarlas dentro de una clase cMesh que estar� gestionada por una clase
//cMeshManager que sigue el patr�n de recursos que ya hemos usado con anterioridad
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

#ifdef _DEBUG
	ShowInfo(lpScene,macFile);
#endif
}


//Es por ello que nosotros recorreremos el �rbol una vez para �aplanar� la jerarqu�a del �rbol,
//calculando s�lo una vez las matrices de mundo para cada malla y asumiendo que la
//escena permanecer� est�tica. La funci�n que nos ayudar� a aplanar la jerarqu�a y a
//crear los objetos es la siguiente funci�n recursiva:
//La funci�n recibe como par�metros el nodo actual que se debe evaluar y la matriz de
//mundo del padre. Al entrar lo primero que se hace es componer la matriz de mundo
//del nodo actual (el c�digo es un poco farragoso, pero simplemente est� componiendo
//la matriz creando cuatro vectores de tama�o 4). Despu�s calcula la matriz de mundo
//real acumulando la transformaci�n del padre con la que indicaba el presente nodo.
//A continuaci�n se comprueba si este nodo tiene alguna malla asociada y de ser as�, crea
//un nuevo cObject y establece sus datos, para a�adir finalmente el objeto a un vector

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

	mObjectList.push_back(lpSubModel);
	}

	// continue for all child nodes
	for(unsigned luiIndex = 0;luiIndex<lpNode->mNumChildren;++luiIndex)
		ConvertNodesToObjects( lpNode->mChildren[luiIndex], lTransform);
}

void cModel::ShowInfo(string lacFile) { 
	Assimp::Importer lImporter; // Create an instance of the Importer class
	
	// Load the scene
	const aiScene* lpScene = lImporter.ReadFile( lacFile.c_str(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType );

	if( !lpScene ) { // If the import failed, report it
		cout << "[ERROR] Model.ShowInfo: " << lImporter.GetErrorString() << endl;;
		return;
	}
	ShowInfo(lpScene,macFile);
}

void cModel::ShowInfo(const aiScene* lpScene, string lacFile) {

	cout << " " << endl;
	cout << "[INFO] Model.ShowInfo: " << lacFile << endl;
	cout << "{ NumChildren=" << lpScene->mRootNode->mNumChildren << ", ";
	cout << " NumMeshes=" << lpScene->mRootNode->mNumMeshes << ", ";
	cout << " NumVertices[Mesh=0]=" << lpScene->mMeshes[0]->mNumVertices << "}"<<endl;
	for (unsigned int luiIndex=0; luiIndex<lpScene->mRootNode->mNumChildren; luiIndex++) 
	{
		const aiNode *lNode = lpScene->mRootNode->mChildren[luiIndex];
		cout << "* Node Children["<< luiIndex << "]=" << (lNode->mName.data);
		cout << " (mNumMeshes=" << lNode->mNumMeshes << ")"<<endl;

		//lpScene->mMeshes[0]
		ShowInfoMesh(lpScene->mMeshes[0]);
		/*
		string lsNameData = lNode->mName.data;
		if ((lacFile == "./Data/Circuitos/Billar/01/Billar01.DAE") && (lsNameData == "Sphere_01"))
		{
			cObject *lpObject = cObjectManager::Get().GetObject("Pista", "Billar");
			cPhysicsObject *lpPhysicsObject = lpObject->GetPtrPhysicsObject();
			lpPhysicsObject->SetMass(0.0f);
			
			//Calculando radio
			float lfRadius=0.0f;
			
			cVec3 lVertice= cVec3(	lpScene->mMeshes[0]->mVertices[luiIndex].x,	lpScene->mMeshes[0]->mVertices[luiIndex].y,		lpScene->mMeshes[0]->mVertices[luiIndex].z);
			
			cVec3 lvCenter2 = cVec3(0,0,0);

			float lfDistance = (lvCenter2.DistanceTo(lVertice));
			if (lfDistance > lfRadius) 
				lfRadius = lfDistance;
			

			cout << "If: " << lpScene->mMeshes[0]->mVertices[luiIndex].x << " , " << lpScene->mMeshes[0]->mVertices[luiIndex].y << " , " << lpScene->mMeshes[0]->mVertices[luiIndex].z << " R: " << lfRadius << endl;
			btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lpScene->mMeshes[0]->mVertices[luiIndex].x, lpScene->mMeshes[0]->mVertices[luiIndex].y, lpScene->mMeshes[0]->mVertices[luiIndex].z));
			
			btCollisionShape* lbtShape = new btSphereShape(lfRadius); 
			
			
			btRigidBody* lpbtRirigBody = lpPhysicsObject->LocalCreateRigidBody(lpPhysicsObject->GetMass(), lbtLocalTrans, lbtShape);
			lpPhysicsObject->SetRigidBody(lpbtRirigBody);
		}
		*/
	}


	/*
	//Prueba haciendo una pista los collision box directos
	if (lacFile == "./Data/Circuitos/Billar/01/Billar01.DAE")
	{

		cObject *lpObject = cObjectManager::Get().GetObject("Pista", "Billar");
		cPhysicsObject *lpPhysicsObject = lpObject->GetPtrPhysicsObject();
		//cPhysicsPista *lpPhysicsPista = (cPhysicsPista*)lpPhysicsObject;
	
	
	//lpPhysicsObject->LocalCreateSphereRigidBody(lfRadius, lvCenter);

		lpPhysicsObject->SetMass(0.0f);
		
		btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lvCenter.x, lvCenter.y, lvCenter.z));
		//lbtLocalTrans.setIdentity();
		//btCollisionShape* lbtShape = new btBoxShape(btVector3(lVec3.x, lVec3.y, lVec3.z));  
		btCollisionShape* lbtShape = new btSphereShape(lfRadius);
			
		btRigidBody* lpbtRirigBody = lpPhysicsObject->LocalCreateRigidBody(lpPhysicsObject->GetMass(), lbtLocalTrans, lbtShape);
		lpPhysicsObject->SetRigidBody(lpbtRirigBody);
	}
	*/

}

void cModel::ShowInfoMesh(aiMesh* lpMesh) {
	//Calculate vertix center
	cVec3 lvCenter=cVec3(0,0,0);
	cVec3 lvMax=cVec3(0,0,0);
	cVec3 lvMin=cVec3(0,0,0);
	float lfX, lfY, lfZ;
	
	for (unsigned int luiIndex=0; luiIndex<(lpMesh->mNumVertices); luiIndex++) {
		lfX = lpMesh->mVertices[luiIndex].x;
		lfY = lpMesh->mVertices[luiIndex].y;
		lfZ = lpMesh->mVertices[luiIndex].z;
		if (lfX>lvMax.x) lvMax.x=lfX;
		if (lfY>lvMax.y) lvMax.y=lfY;
		if (lfZ>lvMax.z) lvMax.z=lfZ;
		if (lfX<lvMin.x) lvMin.x=lfX;
		if (lfY<lvMin.y) lvMin.y=lfY;
		if (lfZ<lvMin.z) lvMin.z=lfZ;
	}
	cout <<" > Bounding Box"<<endl;
	cout <<"   - X:{"<<lvMin.x<<", "<<lvMax.x<<"} Y:{"<<lvMin.y<<", "<<lvMax.y<<"} Z:{"<<lvMin.z<<", "<<lvMax.z<<"}"<<endl;
	lvCenter.x=(lvMax.x-abs(lvMin.x))/2;
	lvCenter.y=(lvMax.y-abs(lvMin.y))/2;
	lvCenter.z=(lvMax.z-abs(lvMin.z))/2;
	cout <<"   - Centro ("<<lvCenter.x<<", "<<lvCenter.y<<", "<<lvCenter.z<<") "<<endl;

	//Calculate radius
	float lfRadius=lvCenter.DistanceTo(lvMin);
	cout << "   - Radio esfera = "<<lfRadius<<endl;
}