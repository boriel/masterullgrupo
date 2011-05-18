#include "SubModel.h"


#include "..\..\Graphics\GraphicManager.h"
#include "..\..\Graphics\Materials\Material.h"
#include "..\..\Graphics\Meshes\Mesh.h"

//Inicialización
void cSubModel::Init()
{
	macName = "";
	mLocalMatrix.LoadIdentity();
	mMeshHandles.resize(0);
	mMaterialHandles.resize(0);
}



void cSubModel::Deinit()
{
	mMeshHandles.resize(0);
	mMaterialHandles.resize(0);
}

//Añade los dos parametros que entra por la función a los arrays
void cSubModel::AddMesh( cResourceHandle lMeshHandle, cResourceHandle lMaterialHandle )
{
	mMeshHandles.push_back( lMeshHandle );
	mMaterialHandles.push_back( lMaterialHandle );
}


//Update
void cSubModel::Update( float lfTimestep )
{
	//Recorre todas las mallas y las actualiza
	for ( unsigned luiIndex = 0; luiIndex < mMeshHandles.size(); ++luiIndex )
	{
		cMesh *lpMesh = (cMesh *)mMeshHandles[luiIndex].GetResource();
		lpMesh->Update(lfTimestep);
	}

}



//La función Render, que lo que hará será iterar por las mallas y materiales y establecerlos, 
//junto con la matriz de mundo correspondiente
//void cSubModel::Render()
void cSubModel::Render(cMatrix &lWorld)
{

	// Set World Matrix
	//cGraphicManager::Get().SetWorldMatrix(mLocalMatrix);
	cGraphicManager::Get().SetWorldMatrix(mLocalMatrix * lWorld);
	for (unsigned luiIndex = 0; luiIndex < mMeshHandles.size(); ++luiIndex)
	{
		// Set the material
		cMaterial * lpMaterial = ( cMaterial *)mMaterialHandles[luiIndex].GetResource();
		cMesh *lpMesh = (cMesh *)mMeshHandles[luiIndex].GetResource();

		// Prepare all the parameters for the render
		lpMaterial->PrepareRender();
		lpMesh->PrepareRender (mMaterialHandles[luiIndex]);
	
		// Set the first pass
		bool lbContinue = lpMaterial->SetFirstPass();
		while (lbContinue)
		{
			// Render Mesh
			lpMesh->RenderMesh();
			// Prepare the next pass
			lbContinue = lpMaterial->SetNextPass();
			}
	}
	/*
	viejo borrar
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
	*/
}