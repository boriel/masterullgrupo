#include "PhysicsPistaMal.h"

/*
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
	//mpGroundShape = new btStaticPlaneShape(btVector3(0,1,0),1); 
	mpGroundShape = new btBoxShape(btVector3(25,0.5,25)); 
	mpbtShape = new btBoxShape(btVector3(25,0.5,25)); 

	//btBoxShape mm;
	

	btVector3 btPosition = btVector3(lPosition.x, lPosition.y, lPosition.z);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btPosition));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, mpGroundShape, btVector3(0,0,0));
	groundRigidBodyCI.m_friction = 10.5f;
	mpbtRigidBody = new btRigidBody(groundRigidBodyCI);
	
	lpDynamicsWorld->addRigidBody(mpbtRigidBody);


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
 
	//lpDynamicsWorld->removeRigidBody(mpGroundRigidBody);
	delete mpbtRigidBody->getMotionState();
	delete mpbtRigidBody;
 
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
	mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform); 

	//Pintando los ejes de coordenadas
	RenderTransformDebug(lbtTransform, 1.0);

	
	//Dibujando un cubo, sacado de btCollisionWorld.cpp 1217 (despues de mucho buscar y seguir codigo ...)
	btCollisionShape* lbtShape = mpbtRigidBody->getCollisionShape();
	const btStaticPlaneShape* lbtStaticPlaneShape = static_cast<const btStaticPlaneShape*>(lbtShape);
	btScalar lbtPlaneConst = lbtStaticPlaneShape->getPlaneConstant();
	const btVector3& lbtPlaneNormal = lbtStaticPlaneShape->getPlaneNormal();
	btVector3 lbtColor(1.0f, 0.0f, 0.0f); //si se pasa por parametro a lo mejor podemos dibujar cosas de muchos colores
	
	RenderPlaneDebug(lbtPlaneNormal, lbtPlaneConst, lbtTransform, lbtColor);




}

*/