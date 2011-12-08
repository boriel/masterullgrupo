#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#include <stdlib.h>

class cObjectAgent; // se pone así para evitar doble inclusion

class cBehaviour {
protected:
    cObjectAgent *mpCharacter;

public:
	//Inicializa los atributos del comportamiento y es llamada en el
	//momento en que se asocia este comportamiento a un personaje
	virtual bool Init(cObjectAgent *lpCharacter);

	//Deinicializa los atributos del comportamiento y es llamada en el
	//momento en que se elimina este comportamiento de un personaje
	virtual void Deinit();

	//Esta función se llama cada frame para actualizar la lógica asociada
	//al comportamiento (Behaviuor)
	virtual void Update(float lfTimestep) = 0;

    cBehaviour(): mpCharacter(NULL) {}
};


#endif
