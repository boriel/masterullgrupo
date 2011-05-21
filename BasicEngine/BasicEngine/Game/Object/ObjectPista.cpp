#include "ObjectPista.h"
#include "..\..\Physics\Objects\PhysicsPista.h"


cObjectPista::cObjectPista (cObject lObject)
{
	Init (lObject.GetPosition(), lObject.GetType(), lObject.GetModelName(), lObject.GetModelFile());
	mPhysicsObject = new cPhysicsPista;
	((cPhysicsPista*)mPhysicsObject)->Init(this->GetPosition());
}

void cObjectPista::Update( float lfTimestep )
{

	//mPosition = ((cPhysicsPista*)mPhysicsObject)->GetPosition();
	//mWorldMatrix.SetPosition(mPosition);

	
}
