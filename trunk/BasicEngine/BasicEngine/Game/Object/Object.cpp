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

}


void cObject::Deinit()
{
	//
}



//void cObject::Render(cMatrix &lWorld)
void cObject::Render()
{
	

	//Pintando el modelo
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
