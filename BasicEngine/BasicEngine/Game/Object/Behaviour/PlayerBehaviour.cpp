

#include "PlayerBehaviour.h"


void cPlayerBehaviour::Deinit()
{
	mpAgent = NULL;
}


void cPlayerBehaviour::Init(cObjectAgent *lpAgent)
{
	mpAgent = (cObjectVehicle *)lpAgent;
}



void cPlayerBehaviour::Update(float lfTimeStep){
	
	// Sonidos
	if (BecomePressed(eIA_Up)){
		cSoundManager::Get().Play(mpAgent->mSoundAcelerar,mpAgent->GetPosition());
		cSoundManager::Get().Play(mpAgent->mSoundCorriendo,mpAgent->GetPosition(), true);
	}

	if (BecomePressed(eIA_Down))
		cSoundManager::Get().Play(mpAgent->mSoundFrenar,mpAgent->GetPosition());

	if (!IsPressed(eIA_Up))
		cSoundManager::Get().Stop(mpAgent->mSoundCorriendo);

	if (mpAgent->GetPtrPhysicsVehicle()->MarchaAtras()){
		if(mpAgent->mbSuena){
			cSoundManager::Get().Play(mpAgent->mSoundMarchaAtras,mpAgent->GetPosition());
            mpAgent->mbSuena = false;
		}
	} else {
		cSoundManager::Get().Stop(mpAgent->mSoundMarchaAtras);
		mpAgent->mbSuena = true;
	}

	if(BecomeReleased(eIA_Up))
        cSoundManager::Get().Stop(mpAgent->mSoundAcelerar);

	if(BecomeReleased(eIA_Down)){
		cSoundManager::Get().Stop(mpAgent->mSoundFrenar);
		cSoundManager::Get().Stop(mpAgent->mSoundMarchaAtras);
	}
	//Vamos a probar el movimiento del coche, por ahora directamente con la fisica  (no poner los else para que pueda usarse 2 teclas presionadas)
	if (BecomePressed(eIA_Up) || IsPressed(eIA_Up)) 
		((cPhysicsVehicle*)mpAgent->mpPhysicsObject)->SpecialKeyboard(eIA_Up);
	if (BecomePressed(eIA_Down) || IsPressed(eIA_Down)) 
		((cPhysicsVehicle*)mpAgent->mpPhysicsObject)->SpecialKeyboard(eIA_Down);
	if (BecomePressed(eIA_Left) || IsPressed(eIA_Left)) 
		((cPhysicsVehicle*)mpAgent->mpPhysicsObject)->SpecialKeyboard(eIA_Left);
	if (BecomePressed(eIA_Right) || IsPressed(eIA_Right)) 
		((cPhysicsVehicle*)mpAgent->mpPhysicsObject)->SpecialKeyboard(eIA_Right);

	// Activar/Desactivar Derrape
	// if (BecomePressed(eIA_Drift) || IsPressed(eIA_Drift)) 
	//	 ((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Drift);
	// if (BecomeReleased(eIA_Drift))
	//	 ((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboardRelease(eIA_Drift);
	///// ---------------------------------

	if (BecomeReleased(eIA_Up))
		((cPhysicsVehicle*)mpAgent->mpPhysicsObject)->SpecialKeyboardRelease(eIA_Up);
	if (BecomeReleased(eIA_Down))
		((cPhysicsVehicle*)mpAgent->mpPhysicsObject)->SpecialKeyboardRelease(eIA_Down);
	
	//Si no hay giro centramos las ruedas, para ponerlas en su sitio
	if (!(BecomePressed(eIA_Left) || IsPressed(eIA_Left) || BecomePressed(eIA_Right) || IsPressed(eIA_Right)))
		((cPhysicsVehicle*)mpAgent->mpPhysicsObject)->CentrandoRuedas();

	//ver si está acelerando
	if (!(BecomePressed(eIA_Up) || IsPressed(eIA_Up)))
		((cPhysicsVehicle*)mpAgent->mpPhysicsObject)->DesAcelerar();
}

