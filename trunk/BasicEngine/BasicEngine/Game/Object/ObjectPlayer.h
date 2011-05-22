/*
Class ObjectPlayer:

*/


#ifndef OBJECT_PLAYER_H
#define OBJECT_PLAYER_H

#include <string>

#include "Object.h"
#include "..\..\MathLib\MathLib.h"


class cObjectPlayer : public cObject
{

	public: 
		cObjectPlayer () {}
		cObjectPlayer (cObject lObject);
		
		virtual void Update (float lfTimestep);
		virtual void Render (cMatrix &lWorld);


};






#endif