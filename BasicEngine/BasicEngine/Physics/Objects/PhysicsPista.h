/*
class PhysicsPista: 

Nota: Creo que intentaré copiar primero el suelo, para despues la pista o cube envolverlo?


*/

#ifndef PHYSICS_PISTA_H
#define PHYSICS_PISTA_H

#include "..\PhysicsObject.h"
#include "btBulletDynamicsCommon.h" 

#include "..\..\MathLib\MathLib.h"

class cPhysicsPista : public cPhysicsObject 
{
	private:
		//btRigidBody* mpFallRigidBody;
		btRigidBody* mpGroundRigidBody;
		//btCollisionShape* mpFallShape;
		btCollisionShape* mpGroundShape;

	public:
		void Init( const std::string &lacNameID) { macNameID = lacNameID; }
		//cPhysicsPlayer () {}
		void Init(const cVec3 &lPosition);
		void Update(void);
		void Deinit(void);

		//cVec3 GetPosition ();
		void RenderObjectDebug();
		
};

#endif