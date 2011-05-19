
#include "PhysicsManager.h"

bool cPhysicsManager::Init () {
	//========================
	//Creando el mundo físico
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
	lpTemp->Init();

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
	//Actualizamos todos los objetos físicos
	//A lo mejor esto no hace falta...
	lpTemp->Update();

	//mpDynamicsWorld->stepSimulation(1/60.f,10);
	mpDynamicsWorld->stepSimulation(lfTimestep,10); //Actualizamos el mundo
}