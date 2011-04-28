/*
Test para probar la librer�a Bullet

*/


//Demo del Vehicle
#include "VehicleDemo.h"
#include "GlutStuff.h"
#include "GLDebugDrawer.h"
#include "btBulletDynamicsCommon.h"
GLDebugDrawer	gDebugDrawer;



//Demo del helloWorld
#include <iostream>



//Cabeceras para encontrar las funciones de abajo
int DemoVehicle (int argc, char** argv);
int DemoHelloWorld();



//Main Principal
int main(int argc, char** argv)
{

	//Para ir probando cosas o demas demos en este espaci, comentamos y hacemos la llamada a la funcion

	DemoVehicle (argc, argv);
	//DemoHelloWorld();


}








int DemoVehicle (int argc, char** argv)
{

	VehicleDemo* vehicleDemo = new VehicleDemo;

	vehicleDemo->initPhysics();
	vehicleDemo->getDynamicsWorld()->setDebugDrawer(&gDebugDrawer);

	return glutmain(argc, argv, 640, 480, "Bullet Vehicle Demo. http://www.continuousphysics.com/Bullet/phpBB2/", vehicleDemo);


}






//Esto podr�a ir perfectamente otro fichero!
int DemoHelloWorld()
{

	std::cout << "Hello World!" << std::endl;
 
	// Build the broadphase
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
 
	// Set up the collision configuration and dispatcher
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
	// The actual physics solver
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
 
	// The world.
	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-10,0));
 
	// Do_everything_else_here
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
 
	btCollisionShape* fallShape = new btSphereShape(1);
 
 
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);
 
 
	btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
	btScalar mass = 1;
	btVector3 fallInertia(0,0,0);
	fallShape->calculateLocalInertia(mass,fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);
 
 
	for (int i=0 ; i<300 ; i++) 
	{
		dynamicsWorld->stepSimulation(1/60.f,10);
 
		btTransform trans;
		fallRigidBody->getMotionState()->getWorldTransform(trans);
 
		std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
	}
 
	dynamicsWorld->removeRigidBody(fallRigidBody);
	delete fallRigidBody->getMotionState();
	delete fallRigidBody;
 
	dynamicsWorld->removeRigidBody(groundRigidBody);
	delete groundRigidBody->getMotionState();
	delete groundRigidBody;
 
 
	delete fallShape;
 
	delete groundShape;
 
 
	// Clean up behind ourselves like good little programmers
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
 

	return 0;
}

