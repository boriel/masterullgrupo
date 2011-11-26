#include "ObjectVehicle.h"
#include "..\..\Physics\Objects\PhysicsVehicle.h"
#include "..\..\Game\Object\ObjectManager.h"
#include "..\..\Game\Object\RaceControlManager.h"
#include "..\..\Input\InputManager.h"
#include "..\InputConfiguration.h"

cObjectVehicle::cObjectVehicle (cObject lObject)
{
		Init (lObject.GetPosition(), lObject.GetType(), lObject.GetModelName(), lObject.GetModelFile(), lObject.GetRotacionInicial(), lObject.GetScale());
		this->SetPlayer(lObject.GetPlayer());
		//mPhysicsObject = new cPhysicsVehicle;
/*
	mPhysicsObject = new cPhysicsPlayer;
	//mPhysicsObject->Init("Player");
	//((cPhysicsPlayer*)mPhysicsObject)->Init(this->GetPosition());
	((cPhysicsPlayer*)mPhysicsObject)->Init(this->GetPosition(), this->GetRotacionInicial());
*/
}
/*
void cObjectVehicle::InitPhysics ()
{

	((cPhysicsVehicle*)mpPhysicsObject)->Init(mPosition);
}
*/

void cObjectVehicle::Player1Control(){
	//Vamos a probar el movimiento del coche, por ahora directamente con la fisica  (no poner los else para que pueda usarse 2 teclas presionadas)
	if (BecomePressed(eIA_Up) || IsPressed(eIA_Up)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Up);
	if (BecomePressed(eIA_Down) || IsPressed(eIA_Down)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Down);
	if (BecomePressed(eIA_Left) || IsPressed(eIA_Left)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Left);
	if (BecomePressed(eIA_Right) || IsPressed(eIA_Right)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Right);

	// Activar/Desactivar Derrape
	/*if (BecomePressed(eIA_Drift) || IsPressed(eIA_Drift)) 
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Drift);
	if (BecomeReleased(eIA_Drift))
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboardRelease(eIA_Drift);
	*/// ---------------------------------


	if (BecomeReleased(eIA_Up))
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboardRelease(eIA_Up);
	if (BecomeReleased(eIA_Down))
		((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboardRelease(eIA_Down);
	
	//Si no hay giro centramos las ruedas, para ponerlas en su sitio
	if (!(BecomePressed(eIA_Left) || IsPressed(eIA_Left) || BecomePressed(eIA_Right) || IsPressed(eIA_Right)))
		((cPhysicsVehicle*)mpPhysicsObject)->CentrandoRuedas();

	//ver si está acelerando
	if (!(BecomePressed(eIA_Up) || IsPressed(eIA_Up)))
		((cPhysicsVehicle*)mpPhysicsObject)->DesAcelerar();
}

void cObjectVehicle::Update( float lfTimestep )
{
	mPosition = ((cPhysicsVehicle*)mpPhysicsObject)->GetPosition();
	
	//mWorldMatrix.LoadIdentity();
	cQuaternion lQuatRot=((cPhysicsVehicle*)mpPhysicsObject)->GetQuatRotation();
	lQuatRot.AsMatrix(mWorldMatrix);
	mWorldMatrix.SetPosition(mPosition);
	
	//mWorldMatrix.LoadScale(mfScale);
	
	
	// Si somos el player, llamaremos a la función de controlar el coche
	if(this->GetPlayer()=="1")Player1Control();
	//if(this->GetPlayer()=="0") // Aqui pondremos la llamada a los controles por IA
		//((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Up);//if(this->GetPlayer()=="0")IAControl();

	//cInputAction::GetPressedTime();
#ifdef _DAVID
	//Desactivo esto temporalmente
#ifdef _DEBUG
	//cout << "Position Coche: (" << mPosition(1) << ","<< mPosition(2) << ","<< mPosition(3) << ")" << endl;
#endif
	//cInputManager::Get().GetAction(eIA_KeyI).GetPressedTime();


	//cout << "cObjectVehicle::Update = (time) " << cInputManager::Get().GetAction(eIA_KeyJ).GetPressedTime() << endl;
	//cout << "cObjectVehicle::Update = (pressed) " << cInputManager::Get().GetAction(eIA_KeyJ).GetBecomePressed () << endl;
	//cout << "cObjectVehicle::Update = (released) " << cInputManager::Get().GetAction(eIA_KeyJ).GetBecomeReleased () << endl;
	//cout << "cObjectVehicle::Update = (released) " << cInputManager::Get().GetAction(eIA_KeyJ).GetIsPressed() << endl;
#endif	
	
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


//Recargando el vehiculo 
void cObjectVehicle::Reload ()
{
	int lPtoControl=cRaceControlManager::Get().GetPuntoControlFromCar(this->GetModelName());
	// Haremos que se coloque en la posición del ultimo punto de control por el que pasó
	// Guardamos la posición y del coche, ya que el punto de control solo nos da X y Z.
	int lAux=mPosition.y;
	mPosition = cRaceControlManager::Get().GetPositionPuntoControl(lPtoControl);
	mPosition.y = lAux+10;
	//mPosition = GetPosicionInicial();
}