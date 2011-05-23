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
  
	// Do_everything_else_here
/*
	mpGroundShape = new btStaticPlaneShape(btVector3(0,1,0),1); 

	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,mpGroundShape,btVector3(0,0,0));
	mpGroundRigidBody = new btRigidBody(groundRigidBodyCI);
	lpDynamicsWorld->addRigidBody(mpGroundRigidBody);
*/
	
	btVector3 lbtPosition = btVector3(lPosition.x, lPosition.y, lPosition.z);

	//mpFallShape = new btSphereShape(1);
	//mpbtShape = new btBoxShape(btVector3(0.5, 0.5, 0.5)); //parece este el bueno
	mpbtShape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
	//mpbtShape = new btBoxShape(btVector3(0, 0, 0.5)); //intentado dibujar un cubo
	//mpbtShape = new btBoxShape(lbtPosition); //intentado dibujar un cubo

	

	//btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
	
	btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform (btQuaternion(0, 0, 0, 1), lbtPosition));
	//btDefaultMotionState* fallMotionState =	new btDefaultMotionState(btTransform (btQuaternion(0, 0, 0, 1)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	mpbtShape->calculateLocalInertia (mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo lRigidBodyCI (mass, fallMotionState, mpbtShape, fallInertia);
	mpRigidBody = new btRigidBody(lRigidBodyCI);
	lpDynamicsWorld->addRigidBody(mpRigidBody);
}


void cPhysicsPlayer::Update(void) 
{ //Update
	btTransform trans;
	mpRigidBody->getMotionState()->getWorldTransform(trans);
 
	std::cout << "Player: (" << trans.getOrigin().getX() << "," <<  trans.getOrigin().getY() << "," << trans.getOrigin().getZ() << ")" << std::endl;
}



void cPhysicsPlayer::Deinit() 
{ //Deinit
	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	lpDynamicsWorld->removeRigidBody(mpRigidBody);
	delete mpRigidBody->getMotionState();
	delete mpRigidBody;
 
	//lpDynamicsWorld->removeRigidBody(mpGroundRigidBody);
	//delete mpGroundRigidBody->getMotionState();
	//delete mpGroundRigidBody;
 
	delete mpbtShape;
	//delete mpGroundShape;
 }



//Obtenemos la posicion central del objeto
cVec3 cPhysicsPlayer::GetPosition ()
{
	cVec3 lPosition;

	btTransform lbtTransform;
	mpRigidBody->getMotionState()->getWorldTransform(lbtTransform);


	lPosition.x = lbtTransform.getOrigin().getX();
	lPosition.y = lbtTransform.getOrigin().getY();
	lPosition.z = lbtTransform.getOrigin().getZ();

	return lPosition;
}


//no estoy seguro que necesitemos esto
cQuaternion cPhysicsPlayer::GetQuatRotation()
{
	//cVec3 lVecRotation;
	cQuaternion lQuatRotation;

	//implementarlo
	
	btTransform lbtTransform;
	mpRigidBody->getMotionState()->getWorldTransform(lbtTransform);

	btQuaternion lbtQuaternion =  lbtTransform.getRotation();
	
	lQuatRotation.x = lbtQuaternion.getX();
	lQuatRotation.y = lbtQuaternion.getY();
	lQuatRotation.z = lbtQuaternion.getZ();
	lQuatRotation.w = lbtQuaternion.getW();

	//std::cout << "PlayerRotX: " << lbtQuaternion.getX() << std::endl;
	//std::cout << "PlayerRotY: " << lbtQuaternion.getY() << std::endl;
	//std::cout << "PlayerRotZ: " << lbtQuaternion.getZ() << std::endl;
	//std::cout << "PlayerRotW: " << lbtQuaternion.getW() << std::endl;

	return lQuatRotation;
}

void cPhysicsPlayer::Pruebas2()
{
	btTransform lbtTransform;
	mpRigidBody->getMotionState()->getWorldTransform(lbtTransform);

	//btTransformUtil bb; 
}


//NADA POR AHORA, NO LO QUEIRO BORRAR PORQUE HAY QUE HACER LA PARTE DE COMPUND DE LAS MALLAS
//TAMBIEN HABRIA QUE PASAR EL RRIGIDBOY A LA CLASE PRINCIPAL
//Obtenemos la matrix de mundo del objeto
void cPhysicsPlayer::Pruebas()
{
	cMatrix lMatrix;

	//implementarlo
	
	btTransform lbtTransform;
	mpRigidBody->getMotionState()->getWorldTransform(lbtTransform);

	btMatrix3x3 btlMatrix = lbtTransform.getBasis();
	
	btCollisionShape* btlShape = mpRigidBody->getCollisionShape();
	
	//http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?t=5469  //Si es una composicion
	if (mpRigidBody->getCollisionShape()->isCompound())
	{
		btCompoundShape * compound = (btCompoundShape *)mpRigidBody->getCollisionShape();
    for(int i=0 ; i < compound->getNumChildShapes(); i++)
    {
			btCollisionShape * child = compound->getChildShape(i);
    }
	}

	btQuaternion lbtQuaternion =  lbtTransform.getRotation();
	


	//cPhysicsManager::Get().GetDynamicsWorld()->getDebugDrawer() ->setDebugMode(1);

	//btIDebugDraw * btIlDW = new btIDebugDraw();
	btIDebugDraw *m_debugDrawer ;

	m_debugDrawer->DBG_DrawWireframe;

	//cPhysicsManager::Get().GetDynamicsWorld()->setDebugDrawer();
	  //getDebugDrawer()->drawTransform(worldTransform,1);

	btDiscreteDynamicsWorld* lpDynamicsWorld = cPhysicsManager::Get().GetDynamicsWorld();
	//lpDynamicsWorld->debugDrawObject(lbtTransform, btlShape, btVector3(1,0,0));


	//GLDebugDrawer	gDebugDrawer;
	//lpDynamicsWorld->setDebugDrawer(&gDebugDrawer);


	//lpDynamicsWorld->getDebugDrawer()->drawTransform(lbtTransform, 1);
	//m_debugDrawer->drawLine(btVector3(1,0,0),btVector3(1,0,0),btVector3(1,0,0));

	
	RenderTransformDebug(lbtTransform, 1.0);

	

}




void cPhysicsPlayer::RenderObjectDebug()
{

	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);



	//btTransform lbtTransform = GetTransform();

	btTransform lbtTransform; 
	mpRigidBody->getMotionState()->getWorldTransform(lbtTransform); 

	//Pintando los ejes de coordenadas
	RenderTransformDebug(lbtTransform, 1.0);


	
	
	//Dibujando un cubo, sacado de btCollisionWorld.cpp 1217 (despues de mucho buscar y seguir codigo ...)
	btCollisionShape* lbtShape = mpRigidBody->getCollisionShape();
	const btBoxShape* lbtBoxShape = static_cast<const btBoxShape*>(lbtShape);
	btVector3 lbtHalfExtents = lbtBoxShape->getHalfExtentsWithMargin();
	btVector3 lbtColor(1.0f, 0.0f, 0.0f); //si se pasa por parametro a lo mejor podemos dibujar cosas de muchos colores
	RenderBoxDebug(- lbtHalfExtents, lbtHalfExtents, lbtTransform, lbtColor);



	//mPhysicsObject->RenderTransformDebug(((cPhysicsPlayer *)mPhysicsObject)->GetTransform(), 1.0);



	//const btBoxShape* boxShape = static_cast<const btBoxShape*>(shape);
	//			btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
	//			getDebugDrawer()->drawBox(-halfExtents,halfExtents,worldTransform,color);
	//			break;

}