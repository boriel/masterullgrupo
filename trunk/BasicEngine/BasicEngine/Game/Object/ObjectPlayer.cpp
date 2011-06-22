#include "ObjectPlayer.h"
#include "..\..\Physics\Objects\PhysicsPlayer.h"
#include "..\..\Game\Object\ObjectManager.h"
#include "..\InputConfiguration.h"
#include "..\..\Input\InputManager.h"

#include "..\..\Graphics\GraphicManager.h"

cObjectPlayer::cObjectPlayer (cObject lObject)
{
	Init (lObject.GetPosition(), lObject.GetType(), lObject.GetModelName(), lObject.GetModelFile(), lObject.GetRotacionInicial());
	//mPhysicsObject = new cPhysicsPlayer;
}


void cObjectPlayer::Update( float lfTimestep )
{
	mPosition = mpPhysicsObject->GetPosition();
	cQuaternion lQuatRot= mpPhysicsObject->GetQuatRotation();
	lQuatRot.AsMatrix(mWorldMatrix);
	mWorldMatrix.SetPosition(mPosition);

	/*
	if (IsPressed(eIA_PlayerForward)) {
		MoveForwards(0.3f);
	} else if (IsPressed(eIA_PlayerBack)) {
		MoveForwards(-0.1f);
	}
	if (IsPressed(eIA_PlayerLeft)) {
		MoveLeft(0.1f);
	} else if (IsPressed(eIA_PlayerRight)) {
		MoveRight(0.1f); 
	}
	*/

}

void cObjectPlayer::Render () 
{
	//cObject::Render(lWorld);
	cObject::Render();

#ifdef _DEBUG
	//((cPhysicsPlayer*) mPhysicsObject)->RenderObjectDebug();
	//cGraphicManager::Get().DrawAxisGrande();  //temporal
#endif

	//cPhysicsObject::DrawTransform(lbtTransform, 1.0);
}

void cObjectPlayer::MoveForwards(float lfImpulse) {
	cVec3 lvImpulse = GetWorldMatrix().GetFront().Normalize();
	lvImpulse.x *= lfImpulse;
	lvImpulse.y *= lfImpulse;
	lvImpulse.z *= lfImpulse;
	((cPhysicsPlayer*)mpPhysicsObject)->ApplyImpulse(lvImpulse);
}

void cObjectPlayer::MoveLeft(float lfImpulse) {
	cVec3 lvImpulse = (2*GetWorldMatrix().GetFront() + GetWorldMatrix().GetLeft()).Normalize();
	lvImpulse.x *= lfImpulse;
	lvImpulse.y *= lfImpulse;
	lvImpulse.z *= lfImpulse;
	cVec3 lvRelPos = (0.6f * GetWorldMatrix().GetFront().Normalize());

	((cPhysicsPlayer*)mpPhysicsObject)->ApplyImpulse(lvImpulse,lvRelPos);
}

void cObjectPlayer::MoveRight(float lfImpulse) {
	cVec3 lvImpulse = (2*GetWorldMatrix().GetFront() + GetWorldMatrix().GetRight() ).Normalize();
	lvImpulse.x *= lfImpulse;
	lvImpulse.y *= lfImpulse;
	lvImpulse.z *= lfImpulse;
	cVec3 lvRelPos = (0.6f * GetWorldMatrix().GetFront().Normalize());

	((cPhysicsPlayer*)mpPhysicsObject)->ApplyImpulse(lvImpulse,lvRelPos);
}
