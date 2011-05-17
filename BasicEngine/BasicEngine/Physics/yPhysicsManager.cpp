
#include "yPhysicsManager.h"



//Inicializando la clase
bool ycPhysicsManager::Init ()
{


	// Build the broadphase
	mBroadphase = new btDbvtBroadphase();
 
	// Set up the collision configuration and dispatcher
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
 
	// The actual physics solver
	mSolver = new btSequentialImpulseConstraintSolver;
 
	// The world.
	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfiguration);
	mDynamicsWorld->setGravity(btVector3(0,-10,0));
 

	return true;
	
}


bool ycPhysicsManager::Deinit ()
{
	
	// Clean up behind ourselves like good little programmers
	delete mDynamicsWorld;
	delete mSolver;
	delete mDispatcher;
	delete mCollisionConfiguration;
	delete mBroadphase;
 
	return true;
}
