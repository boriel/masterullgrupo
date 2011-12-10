#include "ObjectAgent.h"

void cObjectAgent::Update( float lfTimestep )
{
    cObject::Update(lfTimestep);

	if (mpActiveBehaviour != NULL)
		mpActiveBehaviour->Update(lfTimestep);
}


void cObjectAgent::Init()
{
    cObject::Init();
    mpActiveBehaviour = NULL; // Ningún comportamiento
}


float cObjectAgent::GetYaw()
{
    cQuaternion lTmp = mpPhysicsObject->GetQuatRotation();
    float lfYaw, lfPitch, lfRoll;

    lTmp.AsEuler(lfYaw, lfPitch, lfRoll);

    return lfYaw;
}



void cObjectAgent::SetYaw(float lfNewYaw)
{
    cQuaternion lTmp = mpPhysicsObject->GetQuatRotation();
    float lfYaw, lfPitch, lfRoll;

    lTmp.AsEuler(lfYaw, lfPitch, lfRoll);
    lTmp = lTmp.LoadRotationEuler(lfNewYaw, lfPitch, lfRoll);

    mpPhysicsObject->SetQuatRotation(lTmp);
}



float cObjectAgent::GetRoll()
{
    cQuaternion lTmp = mpPhysicsObject->GetQuatRotation();
    float lfYaw, lfPitch, lfRoll;

    lTmp.AsEuler(lfYaw, lfPitch, lfRoll);

    return lfRoll;
}


void cObjectAgent::SetPitch(float lfNewPitch)
{
    cQuaternion lTmp = mpPhysicsObject->GetQuatRotation();
    float lfYaw, lfPitch, lfRoll;

    lTmp.AsEuler(lfYaw, lfPitch, lfRoll);
    lTmp = lTmp.LoadRotationEuler(lfYaw, lfNewPitch, lfRoll);

    mpPhysicsObject->SetQuatRotation(lTmp);
}



float cObjectAgent::GetPitch()
{
    cQuaternion lTmp = mpPhysicsObject->GetQuatRotation();
    float lfYaw, lfPitch, lfRoll;

    lTmp.AsEuler(lfYaw, lfPitch, lfRoll);

    return lfPitch;
}


void cObjectAgent::SetRoll(float lfNewRoll)
{
    cQuaternion lTmp = mpPhysicsObject->GetQuatRotation();
    float lfYaw, lfPitch, lfRoll;

    lTmp.AsEuler(lfYaw, lfPitch, lfRoll);
    lTmp = lTmp.LoadRotationEuler(lfYaw, lfPitch, lfNewRoll);

    mpPhysicsObject->SetQuatRotation(lTmp);
}


//Devuelve el vector Front del personaje (o sea, el vector que indica hacia donde mira)
cVec3 cObjectAgent::GetFront() 
{
    float lfYaw = GetYaw();

    return cVec3( sinf(lfYaw), 0.0f, cosf(lfYaw) );
}


//Devuelve el vector Left del personaje.
cVec3 cObjectAgent::GetLeft()
{
    float lfYaw = GetYaw();

    return cVec3( sinf(lfYaw + HALF_PI), 0.0f, cosf(lfYaw + HALF_PI) );
}

		
//Devuelve el vector Right del personaje
cVec3 cObjectAgent::GetRight()
{ 
    return -GetLeft();
}


float cObjectAgent::GetAngSpeedX()
{
    btTransform lbtTransform;
    
    return mpPhysicsObject->GetAngSpeed().x;
}


float cObjectAgent::GetAngSpeedY()
{
    btTransform lbtTransform;
    
    return mpPhysicsObject->GetAngSpeed().y;
}


float cObjectAgent::GetAngSpeedZ()
{
    btTransform lbtTransform;
    
    return mpPhysicsObject->GetAngSpeed().z;
}


float cObjectAgent::GetSpeed()
{
    return mpPhysicsObject->GetSpeed();
}
