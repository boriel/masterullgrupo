#include "Object.h"

#include "..\Scene\Model.h"
#include "..\Scene\ModelManager.h"

void cObject::Init()
{
	//Inicializanzado la matrix de mundo a la identidad
	//cMatrix lWorld;
	mWorldMatrix.LoadIdentity();

	mWorldMatrix.SetPosition(mPosition);
	//mWorldMatrix.SetPosition(cVec3(0,-2,0));
	//mWorldMatrix.LoadTranslation(mPosition);
}



void cObject::Render(cMatrix &lWorld)
{

	//Pintando el modelo
	//((cModel *)cModelManager::Get().FindResourceA(msModelName).GetResource())->Render(lWorld);
	((cModel *)cModelManager::Get().FindResourceA(msModelName).GetResource())->Render(mWorldMatrix);
	
	
}

void cObject::Update( float lfTimestep )
{

	
}
