#include "CameraNavigator.h"
#include "..\Input\InputManager.h"
#include "..\Game\InputConfiguration.h"
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
	//cVec3 lFront = GetView().GetFront().Normalize();
	cVec3 lDirection = ((*mpTarget)-(*mpPosition)).Normalize();
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

	mpTarget->x=(sin(a+lfAngle))*m;
	mpTarget->z=(cos(a+lfAngle))*m;

	SetLookAt( (*mpPosition), (*mpTarget));
}

/*

void cCamera::Look()
{
	glRotatef(-RotatedX , 1.0, 0.0, 0.0);
	glRotatef(-RotatedY , 0.0, 1.0, 0.0);
	glRotatef(-RotatedZ , 0.0, 0.0, 1.0);
	glTranslatef( -Position.x, -Position.y, -Position.z );
}



void cCamera::Update(bool keys[],int mouseX,int mouseY)
{
	int middleX,middleY;
	float angle;

	// Move the camera's view by the mouse
	middleX = width  >> 1;
	middleY = height >> 1;

	if(mouseX!=middleX)
	{
		angle = (middleX - mouseX) / 50.0f;
		RotateY(angle);
	}
	if(mouseY!=middleY)
	{
		angle = (middleY - mouseY) / 50.0f;
		RotateX(angle);
	}

	if(keys[GLUT_KEY_UP])		MoveForwards(-speed);				
	if(keys[GLUT_KEY_DOWN])		MoveForwards( speed);
	if(keys[GLUT_KEY_LEFT])		StrafeRight(-speed);
	if(keys[GLUT_KEY_RIGHT])	StrafeRight( speed);
}

void cCameraNavigator::GetViewDir(void) {
	cVec3 lStep1, lStep2;
	float lRotatedY=0;
	float lRotatedX=0;
	float lRotatedZ=0;

	//Rotate around Y-axis:
	lStep1.x = cos( (lRotatedY + 90.0) * PIdiv180);
	lStep1.z = -sin( (lRotatedY + 90.0) * PIdiv180);
	//Rotate around X-axis:
	double cosX = cos (lRotatedX * PIdiv180);
	lStep2.x = lStep1.x * cosX;
	lStep2.z = lStep1.z * cosX;
	lStep2.y = sin(lRotatedX * PIdiv180);
	//Rotation around Z-axis not implemented, so:
	mpViewDir->x = lStep2.x;
	mpViewDir->y = lStep2.y;
	mpViewDir->z = lStep2.z;
}



*/