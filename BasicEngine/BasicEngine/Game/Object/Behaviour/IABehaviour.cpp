#include "IABehaviour.h"
#include "../RaceControlManager.h"

bool cIABehaviour::Init(cObjectAgent *lpCharacter)
{
    cChaserBaseBehaviour::Init(lpCharacter);
    setIAState(IA_INITIAL);

    return true;
}


void cIABehaviour::Update(float lfTimestep)
{
    // Vector hacia el target
    switch (getIAState()) {
    case IA_END:
        // Carrera terminada, no hacemos nada
        return;

    case IA_WAIT:
        // En espera del semáforno, no hacemos nada
        return;

    case IA_INITIAL:
        setIAState(IA_START); // Iniciamos la carrera
        return;

    case IA_START:
        //muiCurrentPoint = RACECONTROLMANAGER.GetNumOfRaceControlPoints() - 1;
        muiCurrentPoint = 0;
        setIAState(IA_NEXTPOINT);
        return;

    case IA_NEXTPOINT:
        nextControlPoint();
        setIAState(IA_RUNNING);
        return;

    case IA_RUNNING:
        DriveCar();
        return;
    }

}


void cIABehaviour::nextControlPoint()
{
    muiCurrentPoint = (++muiCurrentPoint) % RACECONTROLMANAGER.GetNumOfRaceControlPoints();
    mTarget = RACECONTROLMANAGER.GetRaceControlPoint(muiCurrentPoint);
}


void cIABehaviour::DriveCar()
{
    cVec3 lTargetVector = mTarget - mpCharacter->GetPosition();
}
