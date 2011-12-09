#include "Behaviour.h"
	
//Inicializa los atributos del comportamiento y es llamada en el
	
//momento en que se asocia este comportamiento a un personaje
bool cBehaviour::Init(cObjectAgent *lpCharacter){
	return true;
}

	//Deinicializa los atributos del comportamiento y es llamada en el
	//momento en que se elimina este comportamiento de un personaje
void cBehaviour::Deinit(){
}