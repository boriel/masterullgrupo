/*
Class ObjectVehicle:

*/


#ifndef OBJECT_VEHICLE_H
#define OBJECT_VEHICLE_H

#include <string>

#include "Object.h"
#include "..\..\MathLib\MathLib.h"


class cObjectVehicle : public cObject
{

	public: 
		cObjectVehicle () {}
		cObjectVehicle (cObject lObject);
		
		virtual void Update (float lfTimestep);
		//virtual void Render (cMatrix &lWorld);
		virtual void Render ();

		//virtual void InitPhysics();


};






#endif