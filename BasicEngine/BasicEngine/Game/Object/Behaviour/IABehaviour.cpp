#include <math.h>
#include "IABehaviour.h"
#include "../RaceControlManager.h"
#include "../ObjectVehicle.h"

// Devuelve el ángulo formado por 2 vectores (en radianes)
inline static float cVec3Angle(const cVec3 &a, const cVec3 &b)
{
    if (!a.x || !b.x) {
        /* método del producto escalar */
        float lfLength = a.Length() * b.Length();
        if (!lfLength)
            return 0.0f;

        return acos(Dot(a, b) / lfLength);
    }

    float m1 = a.z / a.x; // pendiente de a
    float m2 = b.z / b.x;

    return atan2(m2 - m1, 1 - m2 * m1);
}


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

    case IA_INITIAL: 
        muiCurrentPoint = 0;
        setIAState(IA_WAIT); // Iniciamos la carrera
        return;

    case IA_WAIT:
        // En espera del semáforno, no hacemos nada
        if (RACECONTROLMANAGER.isRaceRunning())
            setIAState(IA_START); // salta al estado siguiente si la carrera no ha empezado
        return;

    case IA_START:
        mLastPosition = mpCharacter->GetPosition();
        setIAState(IA_NEXTPOINT);
        return;

    case IA_NEXTPOINT:
        nextControlPoint();
        setIAState(IA_RUNNING);
        return;

    case IA_RUNNING:
        if (((cObjectVehicle *)mpCharacter)->mCurrentCheckPoint)
            setIAState(IA_NEXTPOINT);
        else
            DriveCar(lfTimestep);
        return;
    }

}


void cIABehaviour::nextControlPoint()
{
    muiCurrentPoint = (++muiCurrentPoint) % RACECONTROLMANAGER.GetNumOfRaceControlPoints();
    mTarget = RACECONTROLMANAGER.GetRaceControlPoint(muiCurrentPoint);
    ((cObjectVehicle *)mpCharacter)->mCurrentCheckPoint = false;
}


void cIABehaviour::DriveCar(float lfTimeStep)
{
    //return; // desactivada
    cVec3 lTargetVector = mTarget - mpCharacter->GetPosition();
    //cVec3 lCurrentVector0 = mpCharacter->GetLinearSpeed();
    cVec3 lCurrentVector = mpCharacter->GetPosition() - mLastPosition;
    //cVec3 lCurrentVector = mpCharacter->GetFront(); // No va


    lTargetVector.y = 0;
    lCurrentVector.y = 0;

    float lAngle = cVec3Angle(lCurrentVector, lTargetVector);
    cObjectVehicle *lpAgent = (cObjectVehicle *)mpCharacter;

    if (lAngle > 0) // Está a la iquierda?
			((cPhysicsVehicle*)lpAgent->mpPhysicsObject)->SpecialKeyboard(eIA_Left);
    else
        if (lAngle < 0)
            ((cPhysicsVehicle*)lpAgent->mpPhysicsObject)->SpecialKeyboard(eIA_Right);
            
    ((cPhysicsVehicle*)lpAgent->mpPhysicsObject)->SpecialKeyboard(eIA_Up);

    mLastPosition = mpCharacter->GetPosition(); // Actualizamos la posición
}
