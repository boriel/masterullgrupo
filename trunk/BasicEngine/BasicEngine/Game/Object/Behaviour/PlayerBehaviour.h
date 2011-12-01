#ifndef __PLAYERBEHAVIOUR_H__
#define __PLAYERBEHAVIOUR_H__

#include "Behaviour.h"
#include "../ObjectVehicle.h"

class cPlayerBehaviour: public cBehaviour
{
private:
	cObjectVehicle *mpAgent;

public:
	//Inicializa el atributo
	virtual void Init(cObjectAgent * lpAgent);

	//Vac�o (NO llama al Deinit del personaje)
	virtual void Deinit();

	//Implementa el comportamiento de moverse en funci�n de las teclas pulsadas
	virtual void Update(float lfTimestep);
};

#endif
