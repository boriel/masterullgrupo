
#include "yPhysicsManager.h"



//Inicializando la clase
bool ycPhysicsManager::Init ()
{


	// Build the broadphase
	btBroadphaseInterface* lBroadphase = new btDbvtBroadphase();
 
	// Set up the collision configuration and dispatcher
	btDefaultCollisionConfiguration* lCollisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* lDispatcher = new btCollisionDispatcher(lCollisionConfiguration);
 
	// The actual physics solver
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
 
	// The world.
	mDynamicsWorld = new btDiscreteDynamicsWorld(lDispatcher, lBroadphase, solver, lCollisionConfiguration);
	mDynamicsWorld->setGravity(btVector3(0,-10,0));
 

	return true;
	
}


bool ycPhysicsManager::Deinit ()
{
	
	// Clean up behind ourselves like good little programmers
	delete mDynamicsWorld;
	//delete solver;
	//delete dispatcher;
	//delete collisionConfiguration;
	//delete broadphase;
 
	return true;
}
