#include "ObjectPlayer.h"
#include "..\..\Physics\Objects\PhysicsPlayer.h"

//#include "..\..\Graphics\GraphicManager.h"


cObjectPlayer::cObjectPlayer (cObject lObject)
{
	Init (lObject.GetPosition(), lObject.GetType(), lObject.GetModelName(), lObject.GetModelFile());

	mPhysicsObject = new cPhysicsPlayer;
	//mPhysicsObject->Init("Player");
	((cPhysicsPlayer*)mPhysicsObject)->Init(this->GetPosition());

}



void cObjectPlayer::Update( float lfTimestep )
{

	cObject::Update(lfTimestep); //Llmando al padre que tiene las fisicas generales

	//Estas dos lineas van bien, o eso parece
	//mPosition = ((cPhysicsPlayer*)mPhysicsObject)->GetPosition();
	//mWorldMatrix.SetPosition(mPosition);
	//mWorldMatrix.LoadTranslation(mPosition);  //creo que es lo mismo esto que el setposition

	
	//Primero ratamos la matriz
	cQuaternion lQuatRot = ((cPhysicsPlayer*)mPhysicsObject)->GetQuatRotation();
	mWorldMatrix.LoadRotation(cVec3(lQuatRot.x, lQuatRot.y, lQuatRot.z), lQuatRot.w);
	
	//Depsues trasladamos la matriz
	mPosition = ((cPhysicsPlayer*)mPhysicsObject)->GetPosition();
	mWorldMatrix.SetPosition(mPosition);

  //cGraphicManager::Get().DrawAxis();

/*
	cQuaternion lQuatRotation = ((cPhysicsPlayer*)mPhysicsObject)->GetQuatRotation();
	cVec3 lVec3 (lQuatRotation.x, lQuatRotation.y, lQuatRotation.z);
	mWorldMatrix.LoadRotation(lVec3, lQuatRotation.w);
	
	mPosition = ((cPhysicsPlayer*)mPhysicsObject)->GetPosition();
	mWorldMatrix.SetPosition(mPosition);
*/

	//mPosition = mPosition + cVec3(-1.0, 0, 0);
	////Probando posiciones
	//mWorldMatrix.SetPosition(mPosition);

	
}
