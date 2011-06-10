#include "CameraNavigator.h"
#include "..\Input\InputManager.h"
#include "..\Game\InputConfiguration.h"
#include "GraphicManager.h"
#include "GLHeaders.h"
#include <math.h>

void cCameraNavigator::Init(void) { 
	mpPosition = new cVec3(10.0f, 5.0f, 10.0f);
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
	if (IsPressed (eIA_Advance)) MoveForwards(0.1f);
	if (IsPressed (eIA_Back)) MoveForwards(-0.1f);
	if (IsPressed (eIA_TurnLeft)) RotateY(+0.05f);
	if (IsPressed (eIA_TurnRight)) RotateY(-0.05f);
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
