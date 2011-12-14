#include "ObjectVehicle.h"
#include "..\..\Physics\Objects\PhysicsVehicle.h"
#include "..\..\Game\Object\ObjectManager.h"
#include "..\..\Game\Object\RaceControlManager.h"
#include "..\..\Input\InputManager.h"
#include "..\InputConfiguration.h"
#include "..\..\MathLib\MathLib.h"
#include "Behaviour\PlayerBehaviour.h"
#include "Behaviour\IABehaviour.h"

cObjectVehicle::cObjectVehicle (cObjectAgent lObject)
{
		cObject::Init (lObject.GetPosition(), lObject.GetType(), lObject.GetModelName(), lObject.GetModelFile(), lObject.GetRotacionInicial(), lObject.GetScale());
		this->SetPlayer(lObject.GetPlayer());

		// Añadimos los sonidos de cada coche
		if (lObject.GetModelName() == "Lambert") {
			Sound *mSoundAcelerar=new Sound();
			this->mSoundAcelerar=cSoundManager::Get().AddSound("/Acelerar/AcelerarProta.wav");

			Sound *mSoundFrenar=new Sound();
			this->mSoundFrenar=cSoundManager::Get().AddSound("/Frenar/FrenarProta.wav");
			
			Sound *mSoundCorriendo=new Sound();
			this->mSoundCorriendo=cSoundManager::Get().AddSound("/Corriendo/CorriendoProta.wav");

			Sound *mSoundMarchaAtras=new Sound();
			this->mSoundMarchaAtras=cSoundManager::Get().AddSound("/MarchaAtras/MarchaAtrasProta.wav");
		} else if (lObject.GetModelName() == "L200") {
			Sound *mSoundAcelerar=new Sound();
			this->mSoundAcelerar=cSoundManager::Get().AddSound("/Acelerar/AcelerarL200.wav");

			Sound *mSoundFrenar=new Sound();
			this->mSoundFrenar=cSoundManager::Get().AddSound("/Frenar/FrenarL200.wav");
			
			Sound *mSoundCorriendo=new Sound();
			this->mSoundCorriendo=cSoundManager::Get().AddSound("/Corriendo/CorriendoL200.wav");

			Sound *mSoundMarchaAtras=new Sound();
			this->mSoundMarchaAtras=cSoundManager::Get().AddSound("/MarchaAtras/MarchaAtrasL200.wav");
		} else if (lObject.GetModelName() == "Jeep") {
			Sound *mSoundAcelerar=new Sound();
			this->mSoundAcelerar=cSoundManager::Get().AddSound("/Acelerar/AcelerarJeep.wav");

			Sound *mSoundFrenar=new Sound();
			this->mSoundFrenar=cSoundManager::Get().AddSound("/Frenar/FrenarJeep.wav");
			
			Sound *mSoundCorriendo=new Sound();
			this->mSoundCorriendo=cSoundManager::Get().AddSound("/Corriendo/CorriendoJeep.wav");

			Sound *mSoundMarchaAtras=new Sound();
			this->mSoundMarchaAtras=cSoundManager::Get().AddSound("/MarchaAtras/MarchaAtrasJeep.wav");
		} else if (lObject.GetModelName() == "Jazz") {
			Sound *mSoundAcelerar=new Sound();
			this->mSoundAcelerar=cSoundManager::Get().AddSound("/Acelerar/AcelerarEnemigo.wav");

			Sound *mSoundFrenar=new Sound();
			this->mSoundFrenar=cSoundManager::Get().AddSound("/Frenar/FrenarEnemigo.wav");
			
			Sound *mSoundCorriendo=new Sound();
			this->mSoundCorriendo=cSoundManager::Get().AddSound("/Corriendo/CorriendoEnemigo.wav");

			Sound *mSoundMarchaAtras=new Sound();
			this->mSoundMarchaAtras=cSoundManager::Get().AddSound("/MarchaAtras/MarchaAtrasEnemigo.wav");
		}

		mbSuena=true;
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
void cObjectVehicle::StopSounds()
{
	cSoundManager::Get().Stop(mSoundAcelerar);
	cSoundManager::Get().Stop(mSoundFrenar);
	cSoundManager::Get().Stop(mSoundCorriendo);
	cSoundManager::Get().Stop(mSoundMarchaAtras);
}

/*
void cObjectVehicle::Player1Control(){
	
	// Sonidos
	if (BecomePressed(eIA_Up)){
		cSoundManager::Get().Play(this->mSoundAcelerar,mPosition);
		cSoundManager::Get().Play(this->mSoundCorriendo,mPosition,true);
	}
	if (BecomePressed(eIA_Down))
		cSoundManager::Get().Play(this->mSoundFrenar,mPosition);
	if (!IsPressed(eIA_Up))
		cSoundManager::Get().Stop(this->mSoundCorriendo);
	if (this->GetPtrPhysicsVehicle()->MarchaAtras()){
		if(mbSuena){
			cSoundManager::Get().Play(this->mSoundMarchaAtras,mPosition);
			mbSuena=false;
		}
	}else{
		cSoundManager::Get().Stop(this->mSoundMarchaAtras);
		mbSuena=true;
	}

	if(BecomeReleased(eIA_Up))cSoundManager::Get().Stop(this->mSoundAcelerar);
	if(BecomeReleased(eIA_Down)){
		cSoundManager::Get().Stop(this->mSoundFrenar);
		cSoundManager::Get().Stop(this->mSoundMarchaAtras);
	}
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
	// if (BecomePressed(eIA_Drift) || IsPressed(eIA_Drift)) 
	//	 ((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboard(eIA_Drift);
	// if (BecomeReleased(eIA_Drift))
	//	 ((cPhysicsVehicle*)mpPhysicsObject)->SpecialKeyboardRelease(eIA_Drift);
	///// ---------------------------------

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
*/

void cObjectVehicle::Init()
{
    cObjectAgent::Init();
}

// Pone un comportamiento al vehículo.
// Si tiene el ID del jugador, pone el comportamiento del jugador.
// En otro caso, pone el de la IA
void cObjectVehicle::SetBehaviour()
{
    if (GetPlayer() == __PLAYER_ID)
		mpActiveBehaviour = new cPlayerBehaviour();
    else
        mpActiveBehaviour = new cIABehaviour();
		
	if (mpActiveBehaviour != NULL)
        mpActiveBehaviour->Init(this);	
}

void cObjectVehicle::Update( float lfTimestep )
{
    cObjectAgent::Update(lfTimestep); // Llamamos al ancestro (el cual contiene el comportamiento)

    // Esto ya lo hace el ancestro
    
    // mPosition = ((cPhysicsVehicle*)mpPhysicsObject)->GetPosition();
	// //mWorldMatrix.LoadIdentity();

    // Esto ya lo hace el ancestro
	// cQuaternion lQuatRot=((cPhysicsVehicle*)mpPhysicsObject)->GetQuatRotation();
	// lQuatRot.AsMatrix(mWorldMatrix);
	// mWorldMatrix.SetPosition(mPosition);

	if(this->GetPlayer() == __PLAYER_ID) {
	    //mWorldMatrix.LoadScale(mfScale);
	
        // Si somos el player, llamaremos a la función de controlar el coche
		//Player1Control();
		// y actualizamos la posicion del sonido
		cSoundManager::Get().SetListenerPosition(mPosition);
	}
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
void cObjectVehicle::Render() 
{	((cIABehaviour*)mpActiveBehaviour)->RenderDebug();
	//cObject::Render(lWorld);
	cObject::Render();

#ifdef _DEBUG
	//((cPhysicsVehicle*) mPhysicsObject)->RenderObjectVehicleDebug();
#endif
	//cPhysicsObject::DrawTransform(lbtTransform, 1.0);
}

//Recargando el vehiculo 
void cObjectVehicle::Reload()
{
	int lPtoControl=cRaceControlManager::Get().GetPuntoControlFromCar(this->GetModelName());
	// Haremos que se coloque en la posición del ultimo punto de control por el que pasó
	// Guardamos la posición y del coche, ya que el punto de control solo nos da X y Z.
	int lAux=mPosition.y;
	//printf("%i,%i,%i",
	mPosition = cRaceControlManager::Get().GetPositionPuntoControl(lPtoControl);
	mPosition.y = lAux + 10;
	//mPosition = GetPosicionInicial();
}



