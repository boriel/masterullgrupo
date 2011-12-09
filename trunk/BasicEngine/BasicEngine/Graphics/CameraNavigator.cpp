#include "CameraNavigator.h"
#include "GraphicManager.h"
#include "GLHeaders.h"
#include "..\Input\InputManager.h"
#include "..\Game\InputConfiguration.h"
#include "..\Game\Object\ObjectManager.h"
#include "..\Game\Object\Object.h"
#include <math.h>

void cCameraNavigator::Init(void) 
{ 
	mpPosition = new cVec3(25.0f, 5.0f, 0.0f);  //no se muy bien si esto inicializa
	mpTarget = new cVec3(0.0f, 0.0f, 0.0f);
	mpMove= new cVec3(0.0f, 0.0f, 0.0f);
	meState = eCN_Stop;

	mfAlturaCamara = 40;  //Altura de la camara que sigue al jugador
	SetLookAt( (*mpPosition), (*mpTarget));

	miPuntoActual = 1;
}

void cCameraNavigator::Deinit(void) 
{
	delete mpPosition;
	delete mpTarget;
	delete mpMove;
}


void cCameraNavigator::Update(void) 
{
	if (IsPressed (eIA_CameraForward)) MoveForwards(0.4f);
	if (IsPressed (eIA_CameraBack)) MoveForwards(-0.4f);
	if (IsPressed (eIA_CameraLeft)) RotateY(+0.05f);
	if (IsPressed (eIA_CameraRight)) RotateY(-0.05f);
	if (IsPressed (eIA_CameraUp)) MoveUp(0.4f);
	if (IsPressed (eIA_CameraDown)) MoveUp(-0.4f);

}

void cCameraNavigator::MoveForwards(GLfloat lfDistance) 
{
	cVec3 lDirection = ((*mpTarget)-(*mpPosition));
	lDirection.y=0;
	lDirection=lDirection.Normalize();
	mpMove->x = (lDirection.x) * lfDistance;
	mpMove->y = (lDirection.y) * lfDistance;
	mpMove->z = (lDirection.z) * lfDistance;
	(*mpPosition)+=(*mpMove);
	(*mpTarget)+=(*mpMove);
	SetLookAt( (*mpPosition), (*mpTarget));
}

void cCameraNavigator::RotateY(GLfloat lfAngle) 
{
	cVec3 lDirection = (*mpTarget)-(*mpPosition);
	float x = lDirection.x;
	float y = lDirection.y;
	float z = lDirection.z;
	float a = atan2(x,z);
	float m = sqrt(x*x+z*z);

	mpTarget->x=mpPosition->x+(sin(a+lfAngle))*m;
	mpTarget->y=mpPosition->y+y;
	mpTarget->z=mpPosition->z+(cos(a+lfAngle))*m;

	SetLookAt( (*mpPosition), (*mpTarget));
}

void cCameraNavigator::MoveUp(GLfloat lfDistance) 
{
	cVec3 lDirection = cVec3(0, lfDistance, 0);
	(*mpPosition) += (lDirection);
	(*mpTarget) += (lDirection);
	SetLookAt( (*mpPosition), (*mpTarget));
}

void cCameraNavigator::Render()
{
	cVec3 lPoint = (*mpTarget);
	cGraphicManager::Get().DrawPoint( lPoint, cVec3(1.0f, 0.0f, 0.0f) );
}

void cCameraNavigator::FollowPlayer(void) 
{
#define CAMERA_PLAYER
	// Obtenemos el coche que maneja el jugador //	cObject* lpObject=cObjectManager::Get().GetObjectA("Vehicle","Jeep");
	cObject* lpObject = cObjectManager::Get().GetObjectPlayer();
	cVec3 lvPosition = lpObject->GetPosition();
	cVec3 lvTarget = lvPosition + lpObject->GetWorldMatrix().GetFront() * 10;
	lvPosition = lvPosition - lpObject->GetWorldMatrix().GetFront() * 10; //5
#ifdef CAMERA_PLAYER
	lvPosition.y += 10;//mfAlturaCamara; //5
#else
	lvPosition.y += 40;
#endif
	SetLookAt(lvPosition, lvTarget);
}

void cCameraNavigator::ResetAnimacionFinal(){
	// Obtenemos el coche que maneja el jugador //	cObject* lpObject=cObjectManager::Get().GetObjectA("Vehicle","Jeep");
	cObject* lpObject = cObjectManager::Get().GetObjectPlayer();
	cVec3 lvPosition = lpObject->GetPosition();
	*mpTarget = lvPosition + lpObject->GetWorldMatrix().GetFront() * 10;
	*mpPosition = lvPosition - lpObject->GetWorldMatrix().GetFront() * 10; //5
}

void cCameraNavigator::EndRaceAnimation(void) 
{
#define CAMERA_PLAYER
	// Obtenemos el coche que maneja el jugador //	cObject* lpObject=cObjectManager::Get().GetObjectA("Vehicle","Jeep");
	cObject* lpObject = cObjectManager::Get().GetObjectPlayer();
	cVec3 *lvPosition=mpPosition;
	// Hacemos que cada iteracion aumente la altura
	// Ponemos el tope de altura a 100
	if(lvPosition->y<100){
		*mpTarget =  lpObject->GetPosition();
		lvPosition->y+=1;
	}
	if(lvPosition->z<80)lvPosition->z+=1;
	if(lvPosition->x<80)lvPosition->x+=1;
	else{
		if(mpTarget->x>-80)mpTarget->x-=1;
		if(mpTarget->z>-80)mpTarget->z-=1;
	}
#ifdef CAMERA_PLAYER
	//lvPosition.y += 5;//mfAlturaCamara; //5
#else
	lvPosition.y += 40;
#endif
	SetLookAt(*lvPosition, *mpTarget);
}



//Con esto haremos que la camara siga un recorrido sola, probablemente al acabar la carrera y se muestre el escenario
void cCameraNavigator::RecorridoLibre()
{
	//Sacar la posicion del player y a patir de aqui hacer el recorrido, quizas hacer que se levante un poco avance, de media vuelta y se aleje hacia arriba, despues seguir un recorrido por las puntas de la habitacion, y quizas circular otra vez al coche y vuelta a empezar?

	//cVec3 lvPunto1 = cVec3(90.0f, 81.0f, -116.0f);

	cVec3 laPuntos[4] = {(cVec3(90.0f, 81.0f, -116.0f)),  (cVec3(-50.0f, 81.0f, -116.0f)), (cVec3(-79.0f, 81.0f, 61.0f)), (cVec3(93.0f, 81.0f, 64.0f))};
	


	GLfloat lglfForward = 1.0f;
	GLfloat lglfUp = 1.0f;
	//bool lbPuntoAlcanzado = true;


	if (mpPosition->x < laPuntos[miPuntoActual].x )
		MoveForwards(lglfForward);
	else
		miPuntoActual = 2;

	if (mpPosition->y < laPuntos[miPuntoActual].y)
		MoveUp(lglfUp);


#ifdef _DEBUG
	cout << "Position x:" << mpPosition->x << " y:" << mpPosition->y << " z:" << mpPosition->z << endl;
#endif



}
