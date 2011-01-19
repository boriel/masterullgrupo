#include "Character.h"

#include "..\Graphics\GraphicManager.h"

void cCharacter::Render()
{
	//Componer la matriz de World
	cMatrix lWorld;
	lWorld.LoadIdentity();
	lWorld.LoadRotation(cVec3(0.0f, 1.0f, 0.0f), mfYaw);
 	lWorld.SetPosition( mPosition );
	
	//Establecer la matriz de World
	cGraphicManager::Get().SetWorldMatrix(lWorld);
	
	//Dibujar el personaje (un punto para indicar su posición y una
	//línea para indicar su orientación) en espacio local. La
	//orientación del personaje por defecto será mirando al eje Z
	//positivo.
	cGraphicManager::Get().DrawPoint( cVec3(0.0f, 0.0f, 0.0f), cVec3(1.0f, 0.0f, 0.0f) );
	cGraphicManager::Get().DrawLine( cVec3(0.0f, 0.0f, 0.0f), cVec3(0.0f, 0.0f, 1.0f), cVec3(1.0f, 0.0f, 0.0f) );
}


void cCharacter::Init()
{
	mpActiveBehaviour = NULL; // Ya se hace en el constructor
}


void cCharacter::Update( float lfTimestep )
{
	if (mpActiveBehaviour != NULL)
		mpActiveBehaviour->Update(lfTimestep);
}


void cCharacter::Deinit()
{
	if (mpActiveBehaviour != NULL)
		mpActiveBehaviour->Deinit();
}


// Constructor de oficio
cCharacter::cCharacter(int liId):
	mfYaw(0), 		//Orientación del personaje (yaw)
	mfSpeed(0),		//Velocidad máxima del personaje
	mfAngSpeed(0),	//Velocidad angular del personaje
	mpActiveBehaviour(NULL),
	miId(liId)
{
}


void cCharacter::SetPosition(const cVec3 &lnewPos)
{
	mPosition = lnewPos;
}


void cCharacter::SetYaw(float lfYaw)
{
	mfYaw = lfYaw;
}


void cCharacter::SetSpeed(float lfSpeed)
{
	mfSpeed = lfSpeed;
}

void cCharacter::SetAngSpeed(float lfAngSpeed)
{
	mfAngSpeed = lfAngSpeed;
}
