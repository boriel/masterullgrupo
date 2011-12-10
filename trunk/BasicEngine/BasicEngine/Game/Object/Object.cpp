#include "Object.h"

#include "..\Scene\Model.h"
#include "..\Scene\ModelManager.h"

#include "..\..\Graphics\GraphicManager.h"
#include "..\Scene\Model.h"

void cObject::Init(cVec3 lPosition, string lsType, string lsModelName, string lsModelFile, cQuaternion lRotacionInicial, float lScale)
{
	mPosition = lPosition;
	msType = lsType;
	msModelName = lsModelName;
	msModelFile = lsModelFile;
	mRotacionInicial = lRotacionInicial;
	mPosicionInicial = lPosition;
	mfScale = lScale;
	Init();
}

void cObject::Init()
{
	//Inicializanzado la matrix de mundo a la identidad
	mWorldMatrix.LoadIdentity();
	mWorldMatrix.SetPosition(mPosition);
	cMatrix Aux;
	mWorldMatrix=mWorldMatrix + Aux.LoadScale(mfScale);
	mWorldMatrix=mWorldMatrix + Aux.LoadRotation(cVec3(mRotacionInicial.x,mRotacionInicial.y,mRotacionInicial.z),0);
	mfMass = 0.0f;

}


void cObject::Deinit()
{
	//Hacer mejor los deletes y la liberación de memoria, y las llamadas
    if (mpPhysicsObject != NULL) {
	    delete mpPhysicsObject;
        mpPhysicsObject = NULL;
    }
}

//void cObject::Render(cMatrix &lWorld)
void cObject::Render()
{
	//Pintando el modelo
	((cModel *)cModelManager::Get().FindResourceA(msModelName).GetResource())->Render(mWorldMatrix);
	
//Pintamos los ejes
#if _DEBUG
	cGraphicManager::Get().DrawAxis();
#endif	
}


void cObject::Update( float lfTimestep )
{
	mPosition = mpPhysicsObject->GetPosition();
    cQuaternion lQuatRot= mpPhysicsObject->GetQuatRotation();
    ///mPosition = ((cPhysicsVehicle*)mpPhysicsObject)->GetPosition();
    ///cQuaternion lQuatRot=((cPhysicsVehicle*)mpPhysicsObject)->GetQuatRotation();

	lQuatRot.AsMatrix(mWorldMatrix);
	//mWorldMatrix.LoadScale(mfScale);
	mWorldMatrix.SetPosition(mPosition);


}

void cObject::InitPhysics()
{
	//Se supone que el objeto ya está inicializado, y su modelo cargado en ModelManager
	//Ahora vamos a inicializar la física del Object, a partir de su tipo y de su Model.GetBounding()

	if (msType=="Pista") {
		mpPhysicsObject->SetMass(0.0f);
		cResourceHandle lpHandle = cModelManager::Get().FindResourceA(msModelName);
		cModel* lpModel = (cModel*) lpHandle.GetResource();
		/*float lfX =(lpModel->GetBounding()).mvMin.x;
		float lfY =(lpModel->GetBounding()).mvMin.y;
		float lfZ =(lpModel->GetBounding()).mvMin.z;

		btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lfX, lfY, lfZ));			
		btCollisionShape* lbtShape = new btSphereShape((lpModel->GetBounding()).mfRadius); 
		btRigidBody* lpbtRirigBody = mpPhysicsObject->LocalCreateRigidBody(mpPhysicsObject->GetMass(), lbtLocalTrans, lbtShape);
		mpPhysicsObject->SetRigidBody(lpbtRirigBody);*/
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

