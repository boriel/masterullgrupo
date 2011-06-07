#include "ObjectVehicle.h"
#include "..\..\Physics\Objects\PhysicsVehicle.h"
#include "..\..\Game\Object\ObjectManager.h"

//#include "..\..\Graphics\GraphicManager.h"


cObjectVehicle::cObjectVehicle (cObject lObject)
{
	Init (lObject.GetPosition(), lObject.GetType(), lObject.GetModelName(), lObject.GetModelFile(), lObject.GetRotacionInicial());
	//mPhysicsObject = new cPhysicsVehicle;
/*
	mPhysicsObject = new cPhysicsPlayer;
	//mPhysicsObject->Init("Player");
	//((cPhysicsPlayer*)mPhysicsObject)->Init(this->GetPosition());
	((cPhysicsPlayer*)mPhysicsObject)->Init(this->GetPosition(), this->GetRotacionInicial());
*/
	
}


void cObjectVehicle::InitPhysics ()
{
	
	
	//((cPhysicsVehicle*)mPhysicsObject)->Init(this->GetPosition(), this->GetRotacionInicial());
	((cPhysicsVehicle*)mPhysicsObject)->Init();
}


void cObjectVehicle::Update( float lfTimestep )
{

	/*
	cObject::Update(lfTimestep); //Llmando al padre que tiene las fisicas generales

	//mPosition = ((cPhysicsPlayer*)mPhysicsObject)->GetPosition();
	//mPosition = mPhysicsObject->GetPosition();
	mPosition = ((cPhysicsVehicle*)mPhysicsObject)->GetPosition();
	//cQuaternion lQuatRot=((cPhysicsPlayer*)mPhysicsObject)->GetQuatRotation();
	//cQuaternion lQuatRot= mPhysicsObject->GetQuatRotation();
	cQuaternion lQuatRot=((cPhysicsVehicle*)mPhysicsObject)->GetQuatRotation();
	lQuatRot.AsMatrix(mWorldMatrix);
	mWorldMatrix.SetPosition(mPosition);
	*/


	
}


//void cObjectPlayer::Render (cMatrix &lWorld) 
void cObjectVehicle::Render () 
{
	//cObject::Render(lWorld);
	//cObject::Render();

#ifdef _DEBUG
	//((cPhysicsVehicle*) mPhysicsObject)->RenderObjectVehicleDebug();
#endif
	//cPhysicsObject::DrawTransform(lbtTransform, 1.0);
}
