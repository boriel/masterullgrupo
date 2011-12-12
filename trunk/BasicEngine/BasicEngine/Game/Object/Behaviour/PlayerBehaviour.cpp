

#include "PlayerBehaviour.h"



void cPlayerBehaviour::Update(float lfTimeStep)
{
    cObjectVehicle *lpAgent = (cObjectVehicle *)mpCharacter;

	if(lpAgent != NULL){
		// Sonidos
		if (BecomePressed(eIA_Up)){
			cSoundManager::Get().Play(lpAgent->mSoundAcelerar, lpAgent->GetPosition());
			cSoundManager::Get().Play(lpAgent->mSoundCorriendo, lpAgent->GetPosition(), true);
		}

		if (BecomePressed(eIA_Down))
			cSoundManager::Get().Play(lpAgent->mSoundFrenar, lpAgent->GetPosition());

		if (!IsPressed(eIA_Up))
			cSoundManager::Get().Stop(lpAgent->mSoundCorriendo);

		if (lpAgent->GetPtrPhysicsVehicle()->MarchaAtras()){
			if(lpAgent->mbSuena){
				cSoundManager::Get().Play(lpAgent->mSoundMarchaAtras, lpAgent->GetPosition());
				lpAgent->mbSuena = false;
			}
		} else {
			cSoundManager::Get().Stop(lpAgent->mSoundMarchaAtras);
			lpAgent->mbSuena = true;
		}

		if(BecomeReleased(eIA_Up))
			cSoundManager::Get().Stop(lpAgent->mSoundAcelerar);

		if(BecomeReleased(eIA_Down)){
			cSoundManager::Get().Stop(lpAgent->mSoundFrenar);
			cSoundManager::Get().Stop(lpAgent->mSoundMarchaAtras);
		}
		//Vamos a probar el movimiento del coche, por ahora directamente con la fisica  (no poner los else para que pueda usarse 2 teclas presionadas)
		if (BecomePressed(eIA_Up) || IsPressed(eIA_Up)) 
			((cPhysicsVehicle*)lpAgent->mpPhysicsObject)->SpecialKeyboard(eIA_Up);
		if (BecomePressed(eIA_Down) || IsPressed(eIA_Down)) 
			((cPhysicsVehicle*)lpAgent->mpPhysicsObject)->SpecialKeyboard(eIA_Down);
		if (BecomePressed(eIA_Left) || IsPressed(eIA_Left)) 
			((cPhysicsVehicle*)lpAgent->mpPhysicsObject)->SpecialKeyboard(eIA_Left);
		if (BecomePressed(eIA_Right) || IsPressed(eIA_Right)) 
			((cPhysicsVehicle*)lpAgent->mpPhysicsObject)->SpecialKeyboard(eIA_Right);

		// Activar/Desactivar Derrape
		// if (BecomePressed(eIA_Drift) || IsPressed(eIA_Drift)) 
		//	 ((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Drift);
		// if (BecomeReleased(eIA_Drift))
		//	 ((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboardRelease(eIA_Drift);
		///// ---------------------------------

		if (BecomeReleased(eIA_Up))
			((cPhysicsVehicle*)lpAgent->mpPhysicsObject)->SpecialKeyboardRelease(eIA_Up);
		if (BecomeReleased(eIA_Down))
			((cPhysicsVehicle*)lpAgent->mpPhysicsObject)->SpecialKeyboardRelease(eIA_Down);
	
		//Si no hay giro centramos las ruedas, para ponerlas en su sitio
		if (!(BecomePressed(eIA_Left) || IsPressed(eIA_Left) || BecomePressed(eIA_Right) || IsPressed(eIA_Right)))
			((cPhysicsVehicle*)lpAgent->mpPhysicsObject)->CentrandoRuedas();

		//ver si está acelerando
		if (!(BecomePressed(eIA_Up) || IsPressed(eIA_Up)))
			((cPhysicsVehicle*)lpAgent->mpPhysicsObject)->DesAcelerar();
	}
}

