#include <stdlib.h>
#include <math.h>

#include "IABehaviour.h"
#include "../RaceControlManager.h"
#include "../ObjectVehicle.h"
#include "../../../Utility/Debug.h"
#include "../../../Graphics/GraphicManager.h"

//#define PI 3.141592654

// Devuelve el ángulo formado por 2 vectores (en radianes)
// sobre el plano XZ
inline static float cVec3Angle(const cVec3 &a, const cVec3 &b)
{
    if (!a.x || !b.x) {
        /* método del producto escalar */
        float lfLength = a.Length() * b.Length();
        if (!lfLength)
            return 0.0f;

        return acos(Dot(a, b) / lfLength);
    }

    float m1 = a.z / a.x; // pendiente de a en el plano XZ
    float m2 = b.z / b.x; // pendiente de b en el plano XZ

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
        muiCurrentPoint = 2;
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
    //mTarget = RACECONTROLMANAGER.GetRaceControlPoint(muiCurrentPoint);
    mTarget = RACECONTROLMANAGER.GetPositionPuntoControl(muiCurrentPoint);
    ((cObjectVehicle *)mpCharacter)->mCurrentCheckPoint = false;
}


void cIABehaviour::DriveCar(float lfTimeStep)
{
    //return; // desactivada
    cVec3 lPosition = mpCharacter->GetPhysPosition();
    cVec3 lVelocity = mpCharacter->GetLinearSpeed();
    cVec3 lAngVelocity = mpCharacter->GetAngularSpeed();
    cVec3 lTargetVector = mTarget - lPosition;
    
    cVec3 lCurrentVector = mpCharacter->GetLinearSpeed();
    //cVec3 lCurrentVector = mpCharacter->GetPosition() - mLastPosition;
    //cVec3 lCurrentVector = mpCharacter->GetFront(); // No va
    cVec3 lPrediction; // Estimación de donde acabará el coche en el siguiente lfTimestep

    
    lTargetVector.y = 0;
    lCurrentVector.y = 0;
    lPosition.y = 0;

    // Posición estimada futura de acuerdo a la velocidad lineal y angular actuales
    // y posición actual (comprobado, funciona bastante bien)
    lPrediction.x = lPosition.x + lfTimeStep * lVelocity.x * cos(lAngVelocity.x);
    lPrediction.y = 0;
    lPrediction.z = lPosition.z + lfTimeStep * lVelocity.z * sin(lAngVelocity.x);

    // Vector hacia el objetivo (futuro)
    cVec3 lTargetVector2 = mTarget - lPrediction;
    lTargetVector2.y = 0;

    // Vector de firección (futuro)
    cVec3 lCurrentVector2 = lPrediction - lPosition; // Vector de dirección futura
    lCurrentVector2.y = 0;

    // Ángulos (en radianes, con signo) de -pi/2 a +pi/2
    // Angulo del vector actual hacia el vector objetivo futuro (>0 => el coche tiene el objetivo a la izqda)
    float lAngle = cVec3Angle(lCurrentVector, lTargetVector);
    // Angulo del vector futuro el vector objetivo futuro (>0 => el coche tiene el objetivo a la izqda)
    float lAngle2 = cVec3Angle(lCurrentVector2, lTargetVector2);

    cObjectVehicle *lpAgent = (cObjectVehicle *)mpCharacter;

    /*
    DEBUG_MSG("Error: (%f, %f)", abs(lPosition.x - mLastPosition.x),
        abs(lPosition.z - mLastPosition.z));
    */

    DEBUG_MSG("Angulo: %f Angulo2: %f", lAngle, lAngle2);
    
    if ((lAngle > 0) && (lAngle2 > 0))// Está a la iquierda?
        pressLEFT();
    else if ((lAngle < 0) && (lAngle2 < 0))
            pressRIGHT();
    else { // Soltamos las teclas de dirección
        releaseLEFT();
        releaseRIGHT();
    }
        
    if (((lAngle > 0) && (lAngle2 > 0)) || ((lAngle < 0) && (lAngle2 < 0)))
        if ((abs(lAngle) > (PI / 2.0)) && mpCharacter->GetSpeed() > 10)
            pressDOWN();
        else
            pressUP();
    else { // Si nos vamos a pasar, disminuimos la velocidad lineal
        if (mpCharacter->GetSpeed() > 10)
            releaseUP();
        //if ( (((float)rand()) / RAND_MAX) < abs(lAngle) / (3.141592654 / 2) )
        //    pressDOWN();
    }

    /*
    cVec3 delta = mpCharacter->GetPosition() - mLastPosition;
    if (delta.Length() < 0.3) // atascado?
        pressDOWN();
    */
    mLastPosition = mpCharacter->GetPhysPosition(); // Actualizamos la posición
}

// Efectores
// Envía la señal de soltar tecla izquierda pulsada al agente
void cIABehaviour::releaseLEFT(void)
{
    if (!keyLEFTpressed)
        return;

    keyLEFTpressed = false;
    ((cObjectVehicle *)mpCharacter)->GetPtrPhysicsVehicle()->SpecialKeyboardRelease(eIA_Left);
}


// Envía la señal de soltar tecla derecha pulsada al agente
void cIABehaviour::releaseRIGHT(void)
{
    if (!keyRIGHTpressed)
        return;
    
    keyRIGHTpressed = false;
    ((cObjectVehicle *)mpCharacter)->GetPtrPhysicsVehicle()->SpecialKeyboardRelease(eIA_Right);
}


// Envía la señal de soltar tecla de avance pulsada al agente
void cIABehaviour::releaseUP(void)
{
    if (!keyUPpressed)
        return;
    
    keyUPpressed = false;
    ((cObjectVehicle *)mpCharacter)->GetPtrPhysicsVehicle()->SpecialKeyboardRelease(eIA_Up);
}


// Envía la señal de soltar tecla retroceso pulsada al agente
void cIABehaviour::releaseDOWN(void)
{
    if (!keyDOWNpressed)
        return;
    
    keyDOWNpressed = false;
    ((cObjectVehicle *)mpCharacter)->GetPtrPhysicsVehicle()->SpecialKeyboardRelease(eIA_Down);
}


// Envía la señal de tecla izquierda pulsada al agente
void cIABehaviour::pressLEFT(void)
{
    if (keyLEFTpressed)
        return;

    releaseRIGHT();
    keyLEFTpressed = true;
    ((cObjectVehicle *)mpCharacter)->GetPtrPhysicsVehicle()->SpecialKeyboard(eIA_Left);
}


// Envía la señal de tecla derecha pulsada al agente
void cIABehaviour::pressRIGHT(void)
{
    if (keyRIGHTpressed)
        return;

    releaseLEFT();
    keyRIGHTpressed = true;
    ((cObjectVehicle *)mpCharacter)->GetPtrPhysicsVehicle()->SpecialKeyboard(eIA_Right);
}


// Envía la señal de tecla de avance pulsada al agente
void cIABehaviour::pressUP(void)
{
    if (keyUPpressed)
        return;

    releaseDOWN();
    keyUPpressed = true;
    ((cObjectVehicle *)mpCharacter)->GetPtrPhysicsVehicle()->SpecialKeyboard(eIA_Up);
}

// Envía la señal de tecla retroceso pulsada al agente
void cIABehaviour::pressDOWN(void)
{
    if (keyDOWNpressed)
        return;

    releaseUP();
    keyDOWNpressed = true;
    ((cObjectVehicle *)mpCharacter)->GetPtrPhysicsVehicle()->SpecialKeyboard(eIA_Down);
}


void cIABehaviour::RenderDebug()
{
    // Pintamos el punto de control objetivo
    // mTarget.y += 20;
    if (((cObjectVehicle *)mpCharacter)->GetPlayer() == __PLAYER_ID)
        return; // El del jugador no

    cGraphicManager::Get().DrawPoint(mTarget,cVec3(1,0,0));
    cGraphicManager::Get().DrawLine(mpCharacter->GetPhysPosition(), mTarget, cVec3(1,0,0));
    DEBUG_MSG("Posicion vehículo IA: %f %f %f", 
        mpCharacter->GetPhysPosition().x,
        mpCharacter->GetPhysPosition().y,
        mpCharacter->GetPhysPosition().z);
    // mTarget.y -= 20;
}

