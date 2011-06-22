#include "ObjectPista.h"
#include "..\..\Physics\Objects\PhysicsPista.h"


cObjectPista::cObjectPista (cObject lObject)
{
	Init (lObject.GetPosition(), lObject.GetType(), lObject.GetModelName(), lObject.GetModelFile(), lObject.GetRotacionInicial());
	//mPhysicsObject = new cPhysicsPista;

	/*
	mPhysicsObject = new cPhysicsPista;
	((cPhysicsPista*)mPhysicsObject)->Init(this->GetPosition(), this->GetRotacionInicial());
	*/
}


void cObjectPista::Update( float lfTimestep )
{
	mPosition = ((cPhysicsPista*)mPhysicsObject)->GetPosition();
	cQuaternion lQuatRot=((cPhysicsPista*)mPhysicsObject)->GetQuatRotation();
	lQuatRot.AsMatrix(mWorldMatrix);
	mWorldMatrix.SetPosition(mPosition);
}

void cObjectPista::Render () 
{
	cObject::Render();
}
