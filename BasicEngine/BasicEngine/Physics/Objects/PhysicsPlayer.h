/*
Ejemplo de Hello world de la web de http://www.bulletphysics.org/mediawiki-1.5.8/index.php?title=Hello_World

*/

#ifndef PHYSICS_PLAYER_H
#define PHYSICS_PLAYER_H

#include "..\PhysicsObject.h"
#include "btBulletDynamicsCommon.h" 

#include "..\..\MathLib\MathLib.h"

class cPhysicsPlayer : public cPhysicsObject 
{
	private:
		//btRigidBody* mpRigidBody;
		//btRigidBody* mpGroundRigidBody;
		//btCollisionShape* mpbtShape;
		//btCollisionShape* mpGroundShape;
		

	public:
		void Init( const std::string &lacNameID) { macNameID = lacNameID; }
		//cPhysicsPlayer () {}
		//void Init(const cVec3 &lPosition);
		void Init(const cVec3 &lPosition, const cVec3 &lCollision);
		void Update(void);
		void Deinit(void);

		//cVec3 GetPosition ();
		//cQuaternion GetQuatRotation();
		
		//btTransform GetTransform() { btTransform lbtTransform; mpbtRigidBody->getMotionState()->getWorldTransform(lbtTransform); return lbtTransform; }  //no se si cargarme esta linea
		

		void Pruebas();		
		
};

#endif