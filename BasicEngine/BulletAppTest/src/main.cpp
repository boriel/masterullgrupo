/*
Test para probar la librería Bullet

*/


//Demo del Vehicle
#include "VehicleDemo.h"
#include "GlutStuff.h"
#include "GLDebugDrawer.h"
#include "btBulletDynamicsCommon.h"
GLDebugDrawer	gDebugDrawer;



//Demo del helloWorld
#include "HelloWorld.h"

//Cabeceras para encontrar las funciones de abajo
int DemoVehicle (int argc, char** argv);
int DemoHelloWorld();


//Main Principal
int main(int argc, char** argv)
{

	//Para ir probando cosas o demas demos en este espaci, comentamos y hacemos la llamada a la funcion

	//DemoVehicle (argc, argv);
	DemoHelloWorld();


}








int DemoVehicle (int argc, char** argv)
{

	VehicleDemo* vehicleDemo = new VehicleDemo;

	vehicleDemo->initPhysics();
	vehicleDemo->getDynamicsWorld()->setDebugDrawer(&gDebugDrawer);

	return glutmain(argc, argv, 640, 480, "Bullet Vehicle Demo. http://www.continuousphysics.com/Bullet/phpBB2/", vehicleDemo);


}





int DemoHelloWorld()
{

	HelloWorld();

	return 0;
}






