#include "Object.h"

#include "..\Scene\Model.h"
#include "..\Scene\ModelManager.h"

#include "..\..\Graphics\GraphicManager.h"

void cObject::Init(cVec3 lPosition, string lsType, string lsModelName, string lsModelFile)
{
	mPosition = lPosition;
	msType = lsType;
	msModelName = lsModelName;
	msModelFile = lsModelFile;

	Init();  

}

void cObject::Init()
{
	//Inicializanzado la matrix de mundo a la identidad
	//cMatrix lWorld;
	mWorldMatrix.LoadIdentity();

	mWorldMatrix.SetPosition(mPosition);
	//mWorldMatrix.SetPosition(cVec3(0,-2,0));
	//mWorldMatrix.LoadTranslation(mPosition);
}


void cObject::Deinit()
{
	//
}



void cObject::Render(cMatrix &lWorld)
{

	//Pintando el modelo
	//((cModel *)cModelManager::Get().FindResourceA(msModelName).GetResource())->Render(lWorld);
	((cModel *)cModelManager::Get().FindResourceA(msModelName).GetResource())->Render(mWorldMatrix);

#if _DEBUG
	cGraphicManager::Get().DrawAxis();
#endif	
	
}

void cObject::Update( float lfTimestep )
{
	mPhysicsObject->Update();	
	
	//mPhysicsObject->
}
