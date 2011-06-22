#include "ObjectVehicle.h"
#include "..\..\Physics\Objects\PhysicsVehicle.h"
#include "..\..\Game\Object\ObjectManager.h"

#include "..\..\Input\InputManager.h"
#include "..\InputConfiguration.h"

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
	((cPhysicsVehicle*)mpPhysicsObject)->Init();
}

void cObjectVehicle::Update( float lfTimestep )
{
	//cObject::Update(lfTimestep); //Llmando al padre que tiene las fisicas generales
	//cObject::Update(lfTimestep); //Llmando al padre que tiene las fisicas generales

	//mPosition = ((cPhysicsPlayer*)mPhysicsObject)->GetPosition();
	//mPosition = mPhysicsObject->GetPosition();
	mPosition = ((cPhysicsVehicle*)mpPhysicsObject)->GetPosition();
	//cQuaternion lQuatRot=((cPhysicsPlayer*)mPhysicsObject)->GetQuatRotation();
	//cQuaternion lQuatRot= mPhysicsObject->GetQuatRotation();
	cQuaternion lQuatRot=((cPhysicsVehicle*)mpPhysicsObject)->GetQuatRotation();
	lQuatRot.AsMatrix(mWorldMatrix);
	mWorldMatrix.SetPosition(mPosition);

	//Vamos a probar el movimiento del coche, por ahora directamente con la fisica  (no poner los else par aque coja 2 teclas presionadas)
	if (BecomePressed(eIA_Up) || IsPressed(eIA_Up)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Up);
	if (BecomePressed(eIA_Down) || IsPressed(eIA_Down)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Down);
	if (BecomePressed(eIA_Left) || IsPressed(eIA_Left)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Left);
	if (BecomePressed(eIA_Right) || IsPressed(eIA_Right)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Right);
	
	//cInputAction::GetPressedTime();

	//cInputManager::Get().GetAction(eIA_KeyI).GetPressedTime();
	
	//cout << "cObjectVehicle::Update = (time) " << cInputManager::Get().GetAction(eIA_KeyJ).GetPressedTime() << endl;
	//cout << "cObjectVehicle::Update = (pressed) " << cInputManager::Get().GetAction(eIA_KeyJ).GetBecomePressed () << endl;
	//cout << "cObjectVehicle::Update = (released) " << cInputManager::Get().GetAction(eIA_KeyJ).GetBecomeReleased () << endl;
	//cout << "cObjectVehicle::Update = (released) " << cInputManager::Get().GetAction(eIA_KeyJ).GetIsPressed() << endl;
	
	
}


//void cObjectPlayer::Render (cMatrix &lWorld) 
void cObjectVehicle::Render () 
{
	//cObject::Render(lWorld);
	cObject::Render();

#ifdef _DEBUG
	//((cPhysicsVehicle*) mPhysicsObject)->RenderObjectVehicleDebug();
#endif
	//cPhysicsObject::DrawTransform(lbtTransform, 1.0);
}
