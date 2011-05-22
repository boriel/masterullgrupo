/*
Class ObjectPista:

*/


#ifndef OBJECT_PISTA_H
#define OBJECT_PISTA_H

#include <string>

#include "Object.h"
#include "..\..\MathLib\MathLib.h"


class cObjectPista : public cObject
{

	public: 
		cObjectPista () {}
		cObjectPista (cObject lObject);
		
		virtual void Update( float lfTimestep );
		//virtual void Render (cMatrix &lWorld);
		virtual void Render ();



};






#endif