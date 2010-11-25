#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

// Lo siguiente es necesario debido a la inclusión recursiva de .h
class cCharacter;

class cBehaviourBase {

public:
	//Inicializa los atributos del comportamiento y es llamada en el
	//momento en que se asocia este comportamiento a un personaje
	virtual void Init(cCharacter * lpCharacter) = 0;

	//Deinicializa los atributos del comportamiento y es llamada en el
	//momento en que se elimina este comportamiento de un personaje
	virtual void Deinit() = 0;

	//Esta función se llama cada frame para actualizar la lógica asociada
	//al comportamiento (Behaviuor)
	virtual void Update(float lfTimestep) = 0;
};


#endif
