#include "PhysicsPista.h"

#include <iostream>
#include <string>

#include "..\PhysicsManager.h"

//void cPhysicsPlayer::Init( const std::string &lacNameID) 
void cPhysicsPista::Init(const cVec3 &lPosition) 
{
	//macNameID = lacNameID;
	//meType =  ePO_Cube;

	//std::cout << "Cubo.Init()" << std::endl;
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
  
	// Do_everything_else_here
	mpGroundShape = new btStaticPlaneShape(btVector3(0,1,0),1); 
	//mpGroundShape = new btStaticPlaneShape(btVector3(0,0,1),1); 

	btVector3 btPosition = btVector3(lPosition.x, lPosition.y, lPosition.z);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btPosition));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,mpGroundShape,btVector3(0,0,0));
	mpGroundRigidBody = new btRigidBody(groundRigidBodyCI);
	lpDynamicsWorld->addRigidBody(mpGroundRigidBody);


	/*
	mpFallShape = new btSphereShape(1);

	//btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
	btVector3 btPosition = btVector3(lPosition.x, lPosition.y, lPosition.z);
	btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btPosition));
	btScalar mass = 1;
	btVector3 fallInertia(0,0,0);
	mpFallShape->calculateLocalInertia(mass,fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,mpFallShape,fallInertia);
	mpFallRigidBody = new btRigidBody(fallRigidBodyCI);
	lpDynamicsWorld->addRigidBody(mpFallRigidBody);
	*/
}


void cPhysicsPista::Update(void) 
{ //Update
	//btTransform trans;
	//mpFallRigidBody->getMotionState()->getWorldTransform(trans);
 
	//std::cout << "sphere heigh (Player): " << trans.getOrigin().getY() << std::endl;
}



void cPhysicsPista::Deinit() 
{ //Deinit
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	//lpDynamicsWorld->removeRigidBody(mpFallRigidBody);
	//delete mpFallRigidBody->getMotionState();
	//delete mpFallRigidBody;
 
	//lpDynamicsWorld->removeRigidBody(mpGroundRigidBody);
	delete mpGroundRigidBody->getMotionState();
	delete mpGroundRigidBody;
 
	//delete mpFallShape;
	delete mpGroundShape;
 }


//cVec3 cPhysicsPista::GetPosition ()
//{
//	cVec3 lPosition;
//
//	btTransform trans;
//	mpFallRigidBody->getMotionState()->getWorldTransform(trans);
//
//	lPosition.x = trans.getOrigin().getX();
//	lPosition.y = trans.getOrigin().getY();
//	lPosition.z = trans.getOrigin().getZ();
//
//	return lPosition;
//}



void cPhysicsPista::RenderObjectDebug()
{

	//btTransform lbtTransform = GetTransform();

	btTransform lbtTransform; 
	mpGroundRigidBody->getMotionState()->getWorldTransform(lbtTransform); 

	//Pintando los ejes de coordenadas
	RenderTransformDebug(lbtTransform, 1.0);

	
	//Dibujando un cubo, sacado de btCollisionWorld.cpp 1217 (despues de mucho buscar y seguir codigo ...)
	btCollisionShape* lbtShape = mpGroundRigidBody->getCollisionShape();
	const btStaticPlaneShape* lbtStaticPlaneShape = static_cast<const btStaticPlaneShape*>(lbtShape);
	btScalar lbtPlaneConst = lbtStaticPlaneShape->getPlaneConstant();
	const btVector3& lbtPlaneNormal = lbtStaticPlaneShape->getPlaneNormal();
	btVector3 lbtColor(1.0f, 0.0f, 0.0f); //si se pasa por parametro a lo mejor podemos dibujar cosas de muchos colores
	
	RenderPlaneDebug(lbtPlaneNormal, lbtPlaneConst, lbtTransform, lbtColor);




}