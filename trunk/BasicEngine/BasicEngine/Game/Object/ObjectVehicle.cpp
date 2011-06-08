#include "ObjectVehicle.h"
#include "..\..\Physics\Objects\PhysicsVehicle.h"
#include "..\..\Game\Object\ObjectManager.h"

#include "..\..\Input\InputManager.h"
#include "..\InputConfiguration.h"


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


	//Vamos a probar el movimiento del coche, por ahora directamente con la fisica
	if (BecomePressed(eIA_KeyI)) 
		((cPhysicsVehicle*)mPhysicsObject)->SpecialKeyboard(eIA_KeyI);
	else if (BecomePressed(eIA_KeyK)) 
		((cPhysicsVehicle*)mPhysicsObject)->SpecialKeyboard(eIA_KeyK);
	else if (BecomePressed(eIA_KeyJ)) 
		((cPhysicsVehicle*)mPhysicsObject)->SpecialKeyboard(eIA_KeyJ);
	else if (BecomePressed(eIA_KeyL)) 
		((cPhysicsVehicle*)mPhysicsObject)->SpecialKeyboard(eIA_KeyL);
	


	
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
