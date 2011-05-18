
#include "PhysicsManager.h"

bool cPhysicsManager::Init () { //Inicializando la clase

	// Build the broadphase
	mpBroadphase = new btDbvtBroadphase();
 
	// Set up the collision configuration and dispatcher
	mpCollisionConfiguration = new btDefaultCollisionConfiguration();
	mpDispatcher = new btCollisionDispatcher(mpCollisionConfiguration);
 
	// The actual physics solver
	mpSolver = new btSequentialImpulseConstraintSolver;
 
	// The world.
	mpDynamicsWorld = new btDiscreteDynamicsWorld(mpDispatcher, mpBroadphase, mpSolver, mpCollisionConfiguration);
	mpDynamicsWorld->setGravity(btVector3(0,-10,0));
 
	return true;	
}

bool cPhysicsManager::Deinit () {
	// Clean up behind ourselves like good little programmers
	delete mpDynamicsWorld;
	delete mpSolver;
	delete mpDispatcher;
	delete mpCollisionConfiguration;
	delete mpBroadphase;
 
	return true;
}
