#include "HelloWorldDavid.h"
#include <iostream>

void cHelloWorldDavid::Init() {
	std::cout << "Hello World! Init" << std::endl;
 
	//========================
	//Creando el objeto físico
	mpBroadphase = new btDbvtBroadphase(); // Build the broadphase

	// Set up the collision configuration and dispatcher
	mpCollisionConfiguration = new btDefaultCollisionConfiguration();
	mpDispatcher = new btCollisionDispatcher(mpCollisionConfiguration);
	
	mpSolver = new btSequentialImpulseConstraintSolver; // The actual physics solver
 
	// The world.
	mpDynamicsWorld = new btDiscreteDynamicsWorld(mpDispatcher, 
		mpBroadphase, mpSolver, mpCollisionConfiguration);
	mpDynamicsWorld->setGravity(btVector3(0,-10,0));
 
	// Do_everything_else_here
	mpGroundShape = new btStaticPlaneShape(btVector3(0,1,0),1); 
	mpFallShape = new btSphereShape(1);
 
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,mpGroundShape,btVector3(0,0,0));
	btRigidBody* mpGroundRigidBody = new btRigidBody(groundRigidBodyCI);
	mpDynamicsWorld->addRigidBody(mpGroundRigidBody);
 
	btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
	btScalar mass = 1;
	btVector3 fallInertia(0,0,0);
	mpFallShape->calculateLocalInertia(mass,fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,mpFallShape,fallInertia);
	btRigidBody* mpFallRigidBody = new btRigidBody(fallRigidBodyCI);
	mpDynamicsWorld->addRigidBody(mpFallRigidBody);
}

void cHelloWorldDavid::Update() { //Update
	for (int i=0 ; i<300 ; i++)  {
		mpDynamicsWorld->stepSimulation(1/60.f,10);
 
		btTransform trans;
		mpFallRigidBody->getMotionState()->getWorldTransform(trans);
 
		std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
	}
}

void cHelloWorldDavid::Deinit() { //Deinit
	mpDynamicsWorld->removeRigidBody(mpFallRigidBody);
	delete mpFallRigidBody->getMotionState();
	delete mpFallRigidBody;
 
	mpDynamicsWorld->removeRigidBody(mpGroundRigidBody);
	delete mpGroundRigidBody->getMotionState();
	delete mpGroundRigidBody;
 
	delete mpFallShape;
	delete mpGroundShape;
 
	// Clean up behind ourselves like good little programmers
	delete mpDynamicsWorld;
	delete mpSolver;
	delete mpDispatcher;
	delete mpCollisionConfiguration;
	delete mpBroadphase;
}

