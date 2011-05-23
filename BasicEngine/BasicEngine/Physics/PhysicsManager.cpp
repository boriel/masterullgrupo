
#include "PhysicsManager.h"

bool cPhysicsManager::Init () 
{
	//========================
	//Creando el mundo físico
	mpBroadphase = new btDbvtBroadphase(); // Build the broadphase

	// Set up the collision configuration and dispatcher
	mpCollisionConfiguration = new btDefaultCollisionConfiguration();
	mpDispatcher = new btCollisionDispatcher(mpCollisionConfiguration);
	
	mpSolver = new btSequentialImpulseConstraintSolver; // The actual physics solver
 
	// The world.
	mpDynamicsWorld = new btDiscreteDynamicsWorld(mpDispatcher, mpBroadphase, mpSolver, mpCollisionConfiguration);
	mpDynamicsWorld->setGravity(btVector3(0,-10,0));
 
	return true;	
}

bool cPhysicsManager::Deinit () 
{
	delete mpDynamicsWorld;
	delete mpSolver;
	delete mpDispatcher;
	delete mpCollisionConfiguration;
	delete mpBroadphase;
 
	return true;
}

//update
void cPhysicsManager::Update(float lfTimestep) 
{ 
	//Actualizamos todos el mundo físicos
	//mpDynamicsWorld->stepSimulation(1/60.f,10);
	mpDynamicsWorld->stepSimulation(lfTimestep,10); //Actualizamos el mundo
}