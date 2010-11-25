#include "ChaserNoOrientation.h"


void cChaserNoOrientation::Update(float lfTimestep)
{
	//Calcular el vector distancia (diferencia entre la posici�n del
	//perseguidor y la posici�n del objetivo a perseguir)
	lDistanceVec = mpCharacter->GetPosition() - mTarget;
	lfDistance = lDistanceVec.Length();

	//Calcular la distancia que se mover� el perseguidor teniendo en
	//cuenta su velocidad m�xima
	float lfDisplacement = mpCharacter->GetSpeed() * lfTimestep;

	//Si la distancia que el perseguidor se va a desplazar es mayor o
	//igual a la distancia que hay a su objetivo, se mueve s�lo hasta el
	//punto objetivo (para no pasarse). Si no, se mueve la distancia
	//establecida (para irse acercando //poco a poco al objetivo)
	if (lfDisplacement >= lfDistance) {
		mpCharacter->SetPosition(mTarget);
	} else {
		//La nueva posici�n del perseguidor ser� igual a su posici�n inicial
		//m�s el desplazamiento que debe hacer en la direcci�n indicada por el
		//vector distancia (para moverse as� en direcci�n a su objetivo)
		mpCharacter->SetPosition(mpCharacter->GetPosition() + ( lfDisplacement * lDistanceVec.Normalize() ));
	}
}

