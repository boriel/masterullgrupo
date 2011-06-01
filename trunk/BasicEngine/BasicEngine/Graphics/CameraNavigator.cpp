#include "CameraNavigator.h"
#include "..\Input\InputManager.h"
#include "..\Game\InputConfiguration.h"
#include "GLHeaders.h"

void cCameraNavigator::Init(void) { 
	mpPosition = new cVec3(12.0f, 4.0f, 3.0f);
	mpTarget = new cVec3(0.0f, 0.0f, 0.0f);
	mpMovement= new cVec3(0.0f, 0.0f, 0.0f);
	mpViewDir= new cVec3(0.0f, 0.0f, 0.0f);
	meState = eCN_Stop;

	SetLookAt( (*mpPosition), (*mpTarget));
}

void cCameraNavigator::Deinit(void) {
	delete mpPosition;
	delete mpTarget;
	delete mpMovement;
}

void cCameraNavigator::Update(void) {
	if (BecomePressed (eIA_Advance)) {
		if (meState==eCN_Advance||meState==eCN_Back) {
			meState=eCN_Stop;
		} else if (meState==eCN_Stop) meState=eCN_Advance; 
	}
	if (BecomePressed (eIA_Back)) {
		if (meState==eCN_Advance||meState==eCN_Back) {
			meState=eCN_Stop;
		} else if (meState==eCN_Stop) meState=eCN_Back;
	}

	if (meState!=eCN_Stop) {
		MoveForwards(0.1f);
		if ((mpPosition->x)<=-12.0f || (mpPosition->x)>=12.0f)	{
			meState=eCN_Stop;
			mpMovement->x=0;
		} 
	}
	SetLookAt( (*mpPosition), (*mpTarget)); 
}

void cCameraNavigator::MoveForwards(GLfloat lfDistance) {
	//cVec3 lFront = GetFront();
	GetViewDir();
	mpMovement->x = (mpViewDir->x) * -lfDistance;
	mpMovement->y = (mpViewDir->y) * -lfDistance;
	mpMovement->z = (mpViewDir->z) * -lfDistance;
	(*mpPosition)+=(*mpMovement);
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

/*

void cCamera::Init(int w,int h,float s)
{
	//Init with standard OGL values:
	Position = cVector3D(0.0,0.0,0.0);
	ViewDir  = cVector3D(0.0,0.0,-1.0);
	ViewDirChanged = false;
	//Only to be sure:
	RotatedX = RotatedY = RotatedZ = 0.0;
	//Screen
	width = w;
	height = h;
	//Step length
	speed = s;
}
void cCamera::Look()
{
	glRotatef(-RotatedX , 1.0, 0.0, 0.0);
	glRotatef(-RotatedY , 0.0, 1.0, 0.0);
	glRotatef(-RotatedZ , 0.0, 0.0, 1.0);
	glTranslatef( -Position.x, -Position.y, -Position.z );
}

void cCamera::GetPosition(cVector3D *pos)
{
	*pos = Position;
}

void cCamera::SetPosition(cVector3D pos)
{
	Position.x = pos.x;
	Position.y = pos.y;
	Position.z = pos.z;
}

void cCamera::GetRotated(cVector3D *rot)
{
	*rot = cVector3D(RotatedX,RotatedY,RotatedZ);
}

void cCamera::Rotate(cVector3D v)
{
	RotatedX = v.x;
	RotatedY = v.y;
	RotatedZ = v.z;
	ViewDirChanged = true;
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



void cCamera::RotateX (GLfloat angle)
{
	RotatedX += angle;
	ViewDirChanged = true;
}

void cCamera::RotateY (GLfloat angle)
{
	RotatedY += angle;
	ViewDirChanged = true;
}

void cCamera::RotateZ (GLfloat angle)
{
	RotatedZ += angle;
	ViewDirChanged = true;
}


void cCamera::StrafeRight ( GLfloat distance )
{
	if (ViewDirChanged) GetViewDir();
	cVector3D MoveVector;
	MoveVector.z = -ViewDir.x * -distance;
	MoveVector.y = 0.0;
	MoveVector.x = ViewDir.z * -distance;
	Position.Add(MoveVector);
}

*/