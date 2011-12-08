#ifndef __PLAYERBEHAVIOUR_H__
#define __PLAYERBEHAVIOUR_H__

#include "Behaviour.h"
#include "../ObjectVehicle.h"

class cPlayerBehaviour: public cBehaviour
{
public:
	//Implementa el comportamiento de moverse en función de las teclas pulsadas
	virtual void Update(float lfTimestep);
};

#endif
