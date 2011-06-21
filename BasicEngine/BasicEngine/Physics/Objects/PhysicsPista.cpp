#include "PhysicsPista.h"

#include <iostream>
#include <string>


#include "..\PhysicsManager.h"
#include "..\..\Graphics\GraphicManager.h"
#include "..\..\Game\Scene\ModelManager.h"
#include "..\..\Game\Scene\Model.h"
#include "..\..\Game\Scene\SubModel.h"

//void cPhysicsPlayer::Init( const std::string &lacNameID) 
//void cPhysicsPista::Init(const cVec3 &lPosition, const cQuaternion &lRotacionInicial) 
void cPhysicsPista::Init(const cVec3 &lPosition) 
{
	/*
	cout << "Begin: Prueba en Pista " << endl;

	//haciendo la pista para la de billar, despues habrá que ponerlo bonito

	SetMass(0.0f);

	//cResourceHandle cc = cModelManager::Get().FindResource("Box_Tapicera");
	//string lsFilename = (".\\Data\\" + std::string("Resources.xml"));
	cResourceHandle lRH = cModelManager::Get().FindResourceA("Billar");
	
	
	cResource *lReso = lRH.GetResource();


	btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lPosition.x, lPosition.y, lPosition.z));

	
	cModel *lModel =	((cModel *)cModelManager::Get().FindResourceA("Billar").GetResource());
	
	typedef std::vector<cSubModel *> cObjectList;
	cObjectList lObjectList = lModel->GetObjectList();

	for (unsigned int luiIndex = 0; luiIndex < lObjectList.size(); luiIndex++)
	{
		cout << lObjectList[luiIndex]->GetName() << endl;
		lObjectList[luiIndex]->
	}
	

	cout << "End: Prueba en Pista" << endl;
	*/
	

	/*
	btTransform lbtLocalTrans (btQuaternion (0,0,0,1), btVector3(lPosition.x, lPosition.y, lPosition.z));
	
	btCollisionShape* lbtShape = new btBoxShape(btVector3(lVec3.x, lVec3.y, lVec3.z));  
			
	btRigidBody* lpbtRirigBody = LocalCreateRigidBody(GetMass(), lbtLocalTrans, lbtShape);
	SetRigidBody(lpbtRirigBody);
	*/




	/*
	//std::cout << "Cubo.Init()" << std::endl;
	//btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	btDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
  
	
	btVector3 lbtPosition = btVector3(lPosition.x, lPosition.y, lPosition.z);


	//mpbtShape = new btBoxShape(btVector3(25, 25, 25));
	//mpbtShape = new btBoxShape(btVector3(25, 25, 1));
	//mpbtShape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
	
	btQuaternion lbtQuaternion;
	if (lRotacionInicial.w != 0)  //no pusieron ángulo o no rotacion en el xml
		lbtQuaternion =  CambiarEje(lRotacionInicial);
	else
		lbtQuaternion = btQuaternion(0, 0, 0, 1);

	
	//lbtQuaternion = btQuaternion(1, 0, 0, 3.1416 / 2);


	btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform (lbtQuaternion, lbtPosition));
	//btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform (btQuaternion(0, 0, 0, 1), lbtPosition));
	//btScalar mass = 0.0f;
	mbtMass = 0.0f;
	//btVector3 fallInertia(0, 0, 0);
	mbtFallInertia = btVector3(0,0,0);
	mpbtShape->calculateLocalInertia (mbtMass, mbtFallInertia);
	btRigidBody::btRigidBodyConstructionInfo lRigidBodyCI (mbtMass, fallMotionState, mpbtShape, mbtFallInertia);
	//lRigidBodyCI.m_friction = 0.5f;
	mpbtRigidBody = new btRigidBody(lRigidBodyCI);
	lpDynamicsWorld->addRigidBody(mpbtRigidBody);
	*/

/*
	cQuaternion lQuatRotation;

	btTransform lbtTransform;
	mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform);

	btQuaternion lbtQuaternion2 =  lbtTransform.getRotation();
*/	
	
}


//Aunque si no se actualiza probablemente esta llamada no hace nada
void cPhysicsPista::Update(void) 
{ //Update
	
	btTransform trans;
	mpbtRigidBody->getMotionState()->getWorldTransform(trans);
 
	std::cout << "Pista: (" << trans.getOrigin().getX() << "," <<  trans.getOrigin().getY() << "," << trans.getOrigin().getZ() << ")" << std::endl;
	
}



void cPhysicsPista::Deinit() 
{ //Deinit
	//btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	btDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld->removeRigidBody(mpbtRigidBody);
	delete mpbtRigidBody->getMotionState();
	delete mpbtRigidBody;
 
 
	delete mpbtShape;
	
 }
