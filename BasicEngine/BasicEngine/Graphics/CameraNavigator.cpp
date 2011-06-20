#include "CameraNavigator.h"
#include "GraphicManager.h"
#include "GLHeaders.h"
#include "..\Input\InputManager.h"
#include "..\Game\InputConfiguration.h"
#include "..\Game\Object\ObjectManager.h"
#include "..\Game\Object\Object.h"
#include <math.h>

void cCameraNavigator::Init(void) { 
	mpPosition = new cVec3(25.0f, 5.0f, 0.0f);
	mpTarget = new cVec3(0.0f, 0.0f, 0.0f);
	mpMove= new cVec3(0.0f, 0.0f, 0.0f);
	meState = eCN_Stop;

	SetLookAt( (*mpPosition), (*mpTarget));
}

void cCameraNavigator::Deinit(void) {
	delete mpPosition;
	delete mpTarget;
	delete mpMove;
}

void cCameraNavigator::Update(void) {
	if (IsPressed (eIA_CameraForward)) MoveForwards(0.1f);
	if (IsPressed (eIA_CameraBack)) MoveForwards(-0.1f);
	if (IsPressed (eIA_CameraLeft)) RotateY(+0.05f);
	if (IsPressed (eIA_CameraRight)) RotateY(-0.05f);
}

void cCameraNavigator::MoveForwards(GLfloat lfDistance) {
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

void cCameraNavigator::RotateY(GLfloat lfAngle) {
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

void cCameraNavigator::Render()
{
	cVec3 lPoint = (*mpTarget);
	cGraphicManager::Get().DrawPoint( lPoint, cVec3(1.0f, 0.0f, 0.0f) );
}

void cCameraNavigator::FollowPlayer(void) 
{
	/*
	cObject* lpObject=cObjectManager::Get().GetObjectA("Player","CarJazz");
	cVec3 lvPosition=lpObject->GetPosition();
	cVec3 lvTarget=lvPosition + lpObject->GetWorldMatrix().GetFront()*2;
	lvPosition =lvPosition - lpObject->GetWorldMatrix().GetFront()*5;
	lvPosition.y+=6;
	SetLookAt(lvPosition,lvTarget);
	*/
	
	//Cambiadno la posicion de la camara
	//cObject* lpObject = cObjectManager::Get().GetObjectA("Vehicle", "VehicleRectangulo");  
	cObject* lpObject = cObjectManager::Get().GetObjectA("Vehicle", "CarJazzVehicle");  
	cVec3 lvPosition=lpObject->GetPosition();
	cVec3 lvTarget=lvPosition + lpObject->GetWorldMatrix().GetFront()*2;
	lvPosition =lvPosition - lpObject->GetWorldMatrix().GetFront()*5;
	lvPosition.y += 40;
	SetLookAt(lvPosition, lvTarget);

}
