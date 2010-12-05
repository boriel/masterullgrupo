#include <stdlib.h>

#include "PlayerController.h"
#include "../../Game/InputConfiguration.h"


void cPlayerController::Deinit()
{
	mpCharacter = NULL;
}


void cPlayerController::Init(cCharacter *lpCharacter)
{
	mpCharacter = lpCharacter;
}



void cPlayerController::Update(float lfTimestep)
{
	if (IsPressed(eIA_Advance)) {
		//Mover al personaje hacia adelante (en la dirección del Front)
		//utilizando su velocidad máxima
		//Calcular la distancia que se moverá el perseguidor teniendo en
		//cuenta su velocidad máxima
		float lfDisplacement = mpCharacter->GetSpeed() * lfTimestep;
		mpCharacter->SetPosition(mpCharacter->GetPosition() + (lfDisplacement * mpCharacter->GetFront()));
	}

	if (IsPressed(eIA_TurnRight)) {
		//Girar al personaje hacia la derecha utilizando su velocidad angular
		//Sentido NEGATIVO
		float lfAngleDisplacement = mpCharacter->GetAngSpeed() * lfTimestep;
		mpCharacter->SetYaw(mpCharacter->GetYaw() - lfAngleDisplacement);
	}

	if (IsPressed(eIA_TurnLeft)) {
		//Girar al personaje hacia la derecha utilizando su velocidad angular
		//Sentido POSITIVO
		float lfAngleDisplacement = mpCharacter->GetAngSpeed() * lfTimestep;
		mpCharacter->SetYaw(mpCharacter->GetYaw() + lfAngleDisplacement);
	}
}

