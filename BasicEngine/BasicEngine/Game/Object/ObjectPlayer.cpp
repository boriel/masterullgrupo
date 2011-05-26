#include "ObjectPlayer.h"
#include "..\..\Physics\Objects\PhysicsPlayer.h"

//#include "..\..\Graphics\GraphicManager.h"


cObjectPlayer::cObjectPlayer (cObject lObject)
{
	Init (lObject.GetPosition(), lObject.GetType(), lObject.GetModelName(), lObject.GetModelFile());

	mPhysicsObject = new cPhysicsPlayer;
	//mPhysicsObject->Init("Player");
	//((cPhysicsPlayer*)mPhysicsObject)->Init(this->GetPosition());
	((cPhysicsPlayer*)mPhysicsObject)->Init(this->GetPosition(), this->GetCollision());

	
}



void cObjectPlayer::Update( float lfTimestep )
{

	cObject::Update(lfTimestep); //Llmando al padre que tiene las fisicas generales

	//mPosition = ((cPhysicsPlayer*)mPhysicsObject)->GetPosition();
	mPosition = mPhysicsObject->GetPosition();
	//cQuaternion lQuatRot=((cPhysicsPlayer*)mPhysicsObject)->GetQuatRotation();
	cQuaternion lQuatRot= mPhysicsObject->GetQuatRotation();
	lQuatRot.AsMatrix(mWorldMatrix);
	mWorldMatrix.SetPosition(mPosition);



	
}


//void cObjectPlayer::Render (cMatrix &lWorld) 
void cObjectPlayer::Render () 
{
	//cObject::Render(lWorld);
	cObject::Render();

#ifdef _DEBUG
	((cPhysicsPlayer*) mPhysicsObject)->RenderObjectDebug();
#endif
	//cPhysicsObject::DrawTransform(lbtTransform, 1.0);
}
