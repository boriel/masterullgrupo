#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

class cObjectAgent; // se pone as� para evitar doble inclusion

class cBehaviour {

public:
	//Inicializa los atributos del comportamiento y es llamada en el
	//momento en que se asocia este comportamiento a un personaje
	virtual void Init(cObjectAgent *lpCharacter) = 0;

	//Deinicializa los atributos del comportamiento y es llamada en el
	//momento en que se elimina este comportamiento de un personaje
	virtual void Deinit() = 0;

	//Esta funci�n se llama cada frame para actualizar la l�gica asociada
	//al comportamiento (Behaviuor)
	virtual void Update(float lfTimestep) = 0;
};


#endif
