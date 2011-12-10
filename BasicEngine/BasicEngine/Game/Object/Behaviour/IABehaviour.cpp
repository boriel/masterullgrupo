#include "IABehaviour.h"
#include "../RaceControlManager.h"


bool cIABehaviour::Init(cObjectAgent *lpCharacter)
{
    cChaserBaseBehaviour::Init(lpCharacter);
    mTarget = RACECONTROLMANAGER.GetRaceControlPoint(muiCurrentPoint);

    return true;
}


void cIABehaviour::Update(float lfTimestep)
{
	
}

