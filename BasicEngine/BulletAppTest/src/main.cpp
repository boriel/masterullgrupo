/*
Test para probar la librería Bullet
*/

//DEMO_1: HelloWorld
//DEMO_2: Vehicle
//#define DEMO_1

//Demo del Vehicle
#include "VehicleDemo.h"
#include "GlutStuff.h"
#include "GLDebugDrawer.h"
#include "btBulletDynamicsCommon.h"

//#ifdef DEMO_1
//Demo del helloWorld
#include "HelloWorld.h"

int DemoHelloWorld() {
	HelloWorld();
	return 0;
}
//#else
//Demo Vehicle
GLDebugDrawer	gDebugDrawer;

int DemoVehicle (int argc, char** argv) {
	VehicleDemo* plVehicleDemo = new VehicleDemo;

	plVehicleDemo->initPhysics();
	plVehicleDemo->getDynamicsWorld()->setDebugDrawer(&gDebugDrawer);

	return glutmain(argc, argv, 640, 480, "Bullet Vehicle Demo. http://www.continuousphysics.com/Bullet/phpBB2/", plVehicleDemo);
}
//#endif

//===============================
//Main Principal
int main(int argc, char** argv) {
	//Para ir probando cosas o demas demos en este espaci, comentamos y hacemos la llamada a la funcion
//#ifdef DEMO_1
	//DemoHelloWorld();
	DemoVehicle (argc, argv);
//#else
	//DemoVehicle (argc, argv);
//#endif
}

