
#include "PhysicsManager.h"


bool cPhysicsManager::Init () {
	//========================
	//Creando el mundo f�sico
	mpBroadphase = new btDbvtBroadphase(); // Build the broadphase

	// Set up the collision configuration and dispatcher
	mpCollisionConfiguration = new btDefaultCollisionConfiguration();
	mpDispatcher = new btCollisionDispatcher(mpCollisionConfiguration);
	
	mpSolver = new btSequentialImpulseConstraintSolver; // The actual physics solver
 
	// The world.
	mpDynamicsWorld = new btDiscreteDynamicsWorld(mpDispatcher, 
		mpBroadphase, mpSolver, mpCollisionConfiguration);
	mpDynamicsWorld->setGravity(btVector3(0,-10,0));
 
	//TODO: Prueba temporal
	lpTemp=new cPhysicsCube();
	lpTemp->Init(mpDynamicsWorld);

	return true;	
}

bool cPhysicsManager::Deinit () {
	lpTemp->Deinit();

	delete mpDynamicsWorld;
	delete mpSolver;
	delete mpDispatcher;
	delete mpCollisionConfiguration;
	delete mpBroadphase;
 
	return true;
}

void cPhysicsManager::Update(float lfTimestep) { //update
	lpTemp->Update(lfTimestep);
}