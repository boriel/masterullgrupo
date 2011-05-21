#include "ObjectPlayer.h"
#include "..\..\Physics\Objects\PhysicsPlayer.h"



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

	mPosition = ((cPhysicsPlayer*)mPhysicsObject)->GetPosition();
	mWorldMatrix.SetPosition(mPosition);


	//mPosition = mPosition + cVec3(-1.0, 0, 0);
	////Probando posiciones
	//mWorldMatrix.SetPosition(mPosition);

	
}
