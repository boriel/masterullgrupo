#include "PhysicsPlayer.h"

#include <iostream>
#include <string>


#include "..\PhysicsManager.h"

//void cPhysicsPlayer::Init( const std::string &lacNameID) 
void cPhysicsPlayer::Init(const cVec3 &lPosition) 
{
	//macNameID = lacNameID;
	meType =  ePO_Cube;

	//std::cout << "Cubo.Init()" << std::endl;
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
  
	// Do_everything_else_here
/*
	mpGroundShape = new btStaticPlaneShape(btVector3(0,1,0),1); 

	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,mpGroundShape,btVector3(0,0,0));
	mpGroundRigidBody = new btRigidBody(groundRigidBodyCI);
	lpDynamicsWorld->addRigidBody(mpGroundRigidBody);
*/

	mpFallShape = new btSphereShape(1);

	//btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
	btVector3 btPosition = btVector3(lPosition.x, lPosition.y, lPosition.z);
	btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btPosition));
	btScalar mass = 1;
	btVector3 fallInertia(0,0,0);
	mpFallShape->calculateLocalInertia(mass,fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,mpFallShape,fallInertia);
	mpFallRigidBody = new btRigidBody(fallRigidBodyCI);
	lpDynamicsWorld->addRigidBody(mpFallRigidBody);
}


void cPhysicsPlayer::Update(void) 
{ //Update
	btTransform trans;
	mpFallRigidBody->getMotionState()->getWorldTransform(trans);
 
	std::cout << "sphere heigh (Player): " << trans.getOrigin().getY() << std::endl;
}



void cPhysicsPlayer::Deinit() 
{ //Deinit
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld->removeRigidBody(mpFallRigidBody);
	delete mpFallRigidBody->getMotionState();
	delete mpFallRigidBody;
 
	//lpDynamicsWorld->removeRigidBody(mpGroundRigidBody);
	//delete mpGroundRigidBody->getMotionState();
	//delete mpGroundRigidBody;
 
	delete mpFallShape;
	//delete mpGroundShape;
 }


cVec3 cPhysicsPlayer::GetPosition ()
{
	cVec3 lPosition;

	btTransform trans;
	mpFallRigidBody->getMotionState()->getWorldTransform(trans);

	lPosition.x = trans.getOrigin().getX();
	lPosition.y = trans.getOrigin().getY();
	lPosition.z = trans.getOrigin().getZ();

	return lPosition;
}
