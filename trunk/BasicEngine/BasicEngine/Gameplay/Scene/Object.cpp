#include "Object.h"


#include "..\..\Graphics\GraphicManager.h"
#include "..\..\Graphics\Materials\Material.h"
#include "..\..\Graphics\Meshes\Mesh.h"

//Inicializaci�n
void cObject::Init()
{
	macName = "";
	mWorldMatrix.LoadIdentity();
	mMeshHandles.resize(0);
	mMaterialHandles.resize(0);
}



void cObject::Deinit()
{
	mMeshHandles.resize(0);
	mMaterialHandles.resize(0);
}

//A�ade los dos parametros que entra por la funci�n a los arrays
void cObject::AddMesh( cResourceHandle lMeshHandle, cResourceHandle lMaterialHandle )
{
	mMeshHandles.push_back( lMeshHandle );
	mMaterialHandles.push_back( lMaterialHandle );
}


//Update
void cObject::Update( float lfTimestep )
{

}



//La funci�n Render, que lo que har� ser� iterar por las mallas y materiales y establecerlos, 
//junto con la matriz de mundo correspondiente
void cObject::Render()
{
	// Set World Matrix
	cGraphicManager::Get().SetWorldMatrix(mWorldMatrix);
	
	for (unsigned luiIndex = 0; luiIndex < mMeshHandles.size(); ++luiIndex)
	{
		// Set the material
		cResource* lpResource;
		lpResource = mMaterialHandles[luiIndex].GetResource();
		assert(lpResource);
		((cMaterial *)lpResource)->SetMaterial();

		// Render Mesh
		lpResource = mMeshHandles[luiIndex].GetResource();
		assert(lpResource);
		((cMesh *)lpResource)->RenderMesh();
	}
}