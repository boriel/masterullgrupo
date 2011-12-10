#include "IABehaviour.h"

bool cChaserWithOrientationBehaviour::Init(cObjectAgent *lpCharacter)
{
    cChaserBaseBehaviour::Init(lpCharacter);
    mTarget = RACECONTROLMANAGER.GetRaceControlPoint(muiCurrentPoint);

    return true;
}


void cChaserWithOrientationBehaviour::Update(float lfTimestep)
{
	
}

