#include "PhysicsPlayer.h"

#include <iostream>
#include <string>


#include "..\PhysicsManager.h"
#include "..\..\Graphics\GraphicManager.h"

//void cPhysicsPlayer::Init( const std::string &lacNameID) 
//void cPhysicsPlayer::Init(const cVec3 &lPosition) 
void cPhysicsPlayer::Init(const cVec3 &lPosition, const cQuaternion &lRotacionInicial) 
{
	//macNameID = lacNameID;
	meType =  ePO_Cube;

	//std::cout << "Cubo.Init()" << std::endl;
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
  
	
	btVector3 lbtPosition = btVector3(lPosition.x, lPosition.y, lPosition.z);

	//El shape lo creamos de antemano
	//mpbtShape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
	//mpbtShape = new btBoxShape(btVector3(2.2, 1.0, 1.0));  //NPI DE PORQUE NO CARGA DEL FICHERO. VER QUE PASA Y PORQUE NO LEE LOS VALORES del xml y estos si, ME VOY A DORMIR YA
	//mpbtShape = new btBoxShape(btVector3(lCollision.x / 2.0f, lCollision.y / 2.0f, lCollision.z / 2.0f));  //haciendo el cubo con lo pasado en xml

	btQuaternion lbtQuaternion;
	if (lRotacionInicial.w != 0)  //no pusieron ángulo o no rotacion en el xml
		lbtQuaternion =  CambiarEje(lRotacionInicial);
	else
		lbtQuaternion = btQuaternion(0, 0, 0, 1);


  //Funciona el cambio de eje, ya que al parecer desde max y opencollada siempre vienen la z up y no se como cambiarlo en max (y desde el dae es un coñazo a cada rato) pues cambio en codigo

	btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform (lbtQuaternion, lbtPosition));
	//btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform (btQuaternion(0, 0, 0, 1), lbtPosition)); //Funciona para si ya viene todo dado cojonudo en el dae, orientado y todo
	mbtMass = 1;
	//btVector3 fallInertia(0, 0, 0);
	mbtFallInertia = btVector3 (0,0,0);
	mpbtShape->calculateLocalInertia (mbtMass, mbtFallInertia);
	btRigidBody::btRigidBodyConstructionInfo lRigidBodyCI (mbtMass, fallMotionState, mpbtShape, mbtFallInertia);
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


