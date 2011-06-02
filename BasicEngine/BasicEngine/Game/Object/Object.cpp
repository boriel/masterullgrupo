#include "Object.h"

#include "..\Scene\Model.h"
#include "..\Scene\ModelManager.h"

#include "..\..\Graphics\GraphicManager.h"


void cObject::Init(cVec3 lPosition, string lsType, string lsModelName, string lsModelFile, cQuaternion lRotacionInicial)
{
	mPosition = lPosition;
	msType = lsType;
	msModelName = lsModelName;
	msModelFile = lsModelFile;
	mRotacionInicial = lRotacionInicial;

	Init();  

}

void cObject::Init()
{
	//Inicializanzado la matrix de mundo a la identidad
	//cMatrix lWorld;
	mWorldMatrix.LoadIdentity();

	mWorldMatrix.SetPosition(mPosition);

	mfScale = 1.0f;
	mPhysicsObject = new cPhysicsObject;

}


void cObject::Deinit()
{
	//Hacer mejor los deletes y la liberación de memoria, y las llamadas

	delete mPhysicsObject;
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

//En teoría los hijos harán este trabajo
void cObject::InitPhysics()
{
	Init();
}