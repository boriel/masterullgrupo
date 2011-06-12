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
	cObject::Update(lfTimestep); //TODO: Llmando al padre que tiene las fisicas generales, aunque esto no hace nada por ahora

	mPosition = mPhysicsObject->GetPosition();
	if (IsPressed(eIA_Advance)) {
		MoveForwards(0.5f);
	} else if (IsPressed(eIA_Back)) {
		MoveForwards(-0.5f);
	}
	if (IsPressed(eIA_TurnLeft)) {
		MoveLeft(0.3f);
	} else if (IsPressed(eIA_TurnRight)) {
		MoveLeft(-0.3f); 
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
	((cPhysicsPlayer*)mPhysicsObject)->ApplyImpulse(lvImpulse);
}

void cObjectPlayer::MoveLeft(float lfImpulse) {
	cVec3 lvImpulse = GetWorldMatrix().GetLeft().Normalize();
	lvImpulse += GetWorldMatrix().GetFront().Normalize();
	lvImpulse = lvImpulse.Normalize();
	lvImpulse.x *= lfImpulse;
	lvImpulse.y *= lfImpulse;
	lvImpulse.z *= lfImpulse;
	cVec3 lvRelPos = GetWorldMatrix().GetFront().Normalize();
	lvRelPos.x*=0.6;
	lvRelPos.y*=0.6;
	lvRelPos.z*=0.6;

	((cPhysicsPlayer*)mPhysicsObject)->ApplyImpulse(lvImpulse,lvRelPos);
}
