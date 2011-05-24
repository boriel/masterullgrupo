#include "PhysicsPlayer.h"

#include <iostream>
#include <string>


#include "..\PhysicsManager.h"
#include "..\..\Graphics\GraphicManager.h"

//void cPhysicsPlayer::Init( const std::string &lacNameID) 
void cPhysicsPlayer::Init(const cVec3 &lPosition) 
{
	//macNameID = lacNameID;
	meType =  ePO_Cube;

	//std::cout << "Cubo.Init()" << std::endl;
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
  
	
	btVector3 lbtPosition = btVector3(lPosition.x, lPosition.y, lPosition.z);

	mpbtShape = new btBoxShape(btVector3(0.5, 0.5, 0.5));

	//btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
	
	btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform (btQuaternion(0, 0, 0, 1), lbtPosition));
	//btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform (btQuaternion(0, 0, 0, 1)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	mpbtShape->calculateLocalInertia (mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo lRigidBodyCI (mass, fallMotionState, mpbtShape, fallInertia);
	//lRigidBodyCI.m_friction = 0.5f;
	mpbtRigidBody = new btRigidBody(lRigidBodyCI);
	lpDynamicsWorld->addRigidBody(mpbtRigidBody);
}


void cPhysicsPlayer::Update(void) 
{ //Update
	btTransform trans;
	mpbtRigidBody->getMotionState()->getWorldTransform(trans);
 
	std::cout << "Player: (" << trans.getOrigin().getX() << "," <<  trans.getOrigin().getY() << "," << trans.getOrigin().getZ() << ")" << std::endl;
}



void cPhysicsPlayer::Deinit() 
{ //Deinit
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld->removeRigidBody(mpbtRigidBody);
	delete mpbtRigidBody->getMotionState();
	delete mpbtRigidBody;
 
 
	delete mpbtShape;
	
 }




//NADA POR AHORA, NO LO QUEIRO BORRAR PORQUE HAY QUE HACER LA PARTE DE COMPUND DE LAS MALLAS
//TAMBIEN HABRIA QUE PASAR EL RRIGIDBOY A LA CLASE PRINCIPAL
//Obtenemos la matrix de mundo del objeto
void cPhysicsPlayer::Pruebas()
{
/*
	cMatrix lMatrix;

	//implementarlo
	
	btTransform lbtTransform;
	mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform);

	btMatrix3x3 btlMatrix = lbtTransform.getBasis();
	
	btCollisionShape* btlShape = mpbtRigidBody->getCollisionShape();
	
	//http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?t=5469  //Si es una composicion
	if (mpbtRigidBody->getCollisionShape()->isCompound())
	{
		btCompoundShape * compound = (btCompoundShape *)mpbtRigidBody->getCollisionShape();
    for(int i=0 ; i < compound->getNumChildShapes(); i++)
    {
			btCollisionShape * child = compound->getChildShape(i);
    }
	}

	btQuaternion lbtQuaternion =  lbtTransform.getRotation();
	

*/

	

}


