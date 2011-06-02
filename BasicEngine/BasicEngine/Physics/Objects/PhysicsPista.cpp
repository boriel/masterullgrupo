#include "PhysicsPista.h"

#include <iostream>
#include <string>


#include "..\PhysicsManager.h"
#include "..\..\Graphics\GraphicManager.h"

//void cPhysicsPlayer::Init( const std::string &lacNameID) 
void cPhysicsPista::Init(const cVec3 &lPosition, const cQuaternion &lRotacionInicial) 
{

	//std::cout << "Cubo.Init()" << std::endl;
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
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

	btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform (lbtQuaternion, lbtPosition));
	//btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform (btQuaternion(0, 0, 0, 1), lbtPosition));
	btScalar mass = 0.0f;
	btVector3 fallInertia(0, 0, 0);
	mpbtShape->calculateLocalInertia (mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo lRigidBodyCI (mass, fallMotionState, mpbtShape, fallInertia);
	//lRigidBodyCI.m_friction = 0.5f;
	mpbtRigidBody = new btRigidBody(lRigidBodyCI);
	lpDynamicsWorld->addRigidBody(mpbtRigidBody);
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
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld->removeRigidBody(mpbtRigidBody);
	delete mpbtRigidBody->getMotionState();
	delete mpbtRigidBody;
 
 
	delete mpbtShape;
	
 }
