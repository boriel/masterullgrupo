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
	
	//Dibujar el personaje (un punto para indicar su posici�n y una
	//l�nea para indicar su orientaci�n) en espacio local. La
	//orientaci�n del personaje por defecto ser� mirando al eje Z
	//positivo.
	cGraphicManager::Get().DrawPoint( cVec3(0.0f, 0.0f, 0.0f), cVec3(1.0f, 0.0f, 0.0f) );
	cGraphicManager::Get().DrawLine( cVec3(0.0f, 0.0f, 0.0f), cVec3(0.0f, 0.0f, 1.0f), cVec3(1.0f, 0.0f, 0.0f) );

}