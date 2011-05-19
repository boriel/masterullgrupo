#include "PhysicsCube.h"
#include "..\PhysicsManager.h"
#include <iostream>
#include <string>

void cPhysicsCube::Init( const std::string &lacNameID) {
	macNameID = lacNameID;

	//std::cout << "Cubo.Init()" << std::endl;
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
  
	// Do_everything_else_here
	mpGroundShape = new btStaticPlaneShape(btVector3(0,1,0),1); 
	mpFallShape = new btSphereShape(1);
 
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,mpGroundShape,btVector3(0,0,0));
	mpGroundRigidBody = new btRigidBody(groundRigidBodyCI);
	lpDynamicsWorld->addRigidBody(mpGroundRigidBody);
 
	btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
	btScalar mass = 1;
	btVector3 fallInertia(0,0,0);
	mpFallShape->calculateLocalInertia(mass,fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,mpFallShape,fallInertia);
	mpFallRigidBody = new btRigidBody(fallRigidBodyCI);
	lpDynamicsWorld->addRigidBody(mpFallRigidBody);
}

void cPhysicsCube::Update(void) { //Update
	btTransform trans;
	mpFallRigidBody->getMotionState()->getWorldTransform(trans);
 
	std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
}

void cPhysicsCube::Deinit() { //Deinit
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld->removeRigidBody(mpFallRigidBody);
	delete mpFallRigidBody->getMotionState();
	delete mpFallRigidBody;
 
	lpDynamicsWorld->removeRigidBody(mpGroundRigidBody);
	delete mpGroundRigidBody->getMotionState();
	delete mpGroundRigidBody;
 
	delete mpFallShape;
	delete mpGroundShape;
 }

