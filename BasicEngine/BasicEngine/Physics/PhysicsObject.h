/*
clase 
	Representa un fisica de un objeto determinado
*/

#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H


#include <string>

#include "PhysicObjectType.h"
//#include "..\MathLib\MathLib.h"


class cPhysicsObject 
{
	public:
		virtual void Init( const std::string &lacNameID) = 0;
		virtual void Update(void) = 0;
		virtual void Deinit(void) = 0;
		std::string GetNameID(void) { return macNameID; }
		ePhysicObjectType GetType(void) { return meType; }

		
		//cVec3 GetPosition ();

	protected:
		std::string macNameID;
		ePhysicObjectType meType;
};

#endif