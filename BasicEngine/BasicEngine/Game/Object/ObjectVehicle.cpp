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
	if (BecomePressed(eIA_KeyI) || IsPressed(eIA_KeyI)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_KeyI);
	if (BecomePressed(eIA_KeyK) || IsPressed(eIA_KeyK)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_KeyK);
	if (BecomePressed(eIA_KeyJ) || IsPressed(eIA_KeyJ)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_KeyJ);
	if (BecomePressed(eIA_KeyL) || IsPressed(eIA_KeyL)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_KeyL);
	
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
