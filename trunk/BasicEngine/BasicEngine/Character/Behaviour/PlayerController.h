#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "behaviourbase.h"
#include "../Character.h"

class cPlayerController: public cBehaviourBase
{
private:
	cCharacter *mpCharacter;

public:
	//Inicializa el atributo
	virtual void Init(cCharacter * lpCharacter);

	//Vacío (NO llama al Deinit del personaje)
	virtual void Deinit();

	//Implementa el comportamiento de moverse en función de las teclas pulsadas
	virtual void Update(float lfTimestep);
};

#endif
