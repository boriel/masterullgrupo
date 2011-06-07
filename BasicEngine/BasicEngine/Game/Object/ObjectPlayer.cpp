#include "ObjectPlayer.h"
#include "..\..\Physics\Objects\PhysicsPlayer.h"
#include "..\..\Game\Object\ObjectManager.h"
#include "..\InputConfiguration.h"
#include "..\..\Input\InputManager.h"

cObjectPlayer::cObjectPlayer (cObject lObject)
{
	Init (lObject.GetPosition(), lObject.GetType(), lObject.GetModelName(), lObject.GetModelFile(), lObject.GetRotacionInicial());
	mPhysicsObject = new cPhysicsPlayer;
/*
	mPhysicsObject = new cPhysicsPlayer;
	//mPhysicsObject->Init("Player");
	//((cPhysicsPlayer*)mPhysicsObject)->Init(this->GetPosition());
	((cPhysicsPlayer*)mPhysicsObject)->Init(this->GetPosition(), this->GetRotacionInicial());
*/
}

void cObjectPlayer::InitPhysics ()
{
	((cPhysicsPlayer*)mPhysicsObject)->Init(this->GetPosition(), this->GetRotacionInicial());
}

void cObjectPlayer::Update( float lfTimestep )
{
	cObject::Update(lfTimestep); //TODO: Llmando al padre que tiene las fisicas generales, aunque esto no hace nada por ahora

	mPosition = mPhysicsObject->GetPosition();
	if (BecomePressed(eIA_Advance)) {
		MoveForwards(0.05f);
	}

	cQuaternion lQuatRot= mPhysicsObject->GetQuatRotation();
	lQuatRot.AsMatrix(mWorldMatrix);
	mWorldMatrix.SetPosition(mPosition);
}

void cObjectPlayer::Render () 
{
	//cObject::Render(lWorld);
	cObject::Render();

#ifdef _DEBUG
	((cPhysicsPlayer*) mPhysicsObject)->RenderObjectDebug();
#endif

	//cPhysicsObject::DrawTransform(lbtTransform, 1.0);
}

void cObjectPlayer::MoveForwards(float lfDistance) {
	cVec3 lDirection = GetWorldMatrix().GetFront().Normalize();
	lDirection.x += lfDistance; 
	mPosition.x += (lDirection.x*lfDistance);
	mPosition.x += 0.001f;
	//TODO: falta algo como PhysicsObject->SetPosition()
	//((cPhysicsPlayer*)mPhysicsObject)->Init(this->GetPosition(), this->GetRotacionInicial());
	cQuaternion lQuatRot= mPhysicsObject->GetQuatRotation();
	((cPhysicsPlayer*)mPhysicsObject)->Init(mPosition,lQuatRot);
	//this->InitPhysics();
}
