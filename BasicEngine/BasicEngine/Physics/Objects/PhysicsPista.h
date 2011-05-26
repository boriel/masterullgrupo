/*

class PhysicsPista: pista del juego, habrá que depurarla

*/

#ifndef PHYSICS_PISTA_H
#define PHYSICS_PISTA_H

#include "..\PhysicsObject.h"
#include "btBulletDynamicsCommon.h" 

#include "..\..\MathLib\MathLib.h"

class cPhysicsPista : public cPhysicsObject 
{
	private:
		

	public:
		void Init( const std::string &lacNameID) { macNameID = lacNameID; }
		void Init(const cVec3 &lPosition, const cQuaternion &lRotacionInicial);
		void Update(void);
		void Deinit(void);
		
		

};

#endif