/*
	Clase Cámara con navegación por el mundo
*/

#ifndef _CAMERA_NAVIGATOR_H
#define _CAMERA_NAVIGATOR_H

#include "Camera.h"

enum eCameraNavigatorStates {
	eCN_Stop = 0,
	eCN_Movement,
	eCN_Count
};

class cCameraNavigator : public cCamera {
	private:
		cVec3 *mpPosition;
		cVec3 *mpTarget;
		cVec3 *mpMovement;
		eCameraNavigatorStates meState;

	public:
		void Init(void);
		void Deinit(void);
		void Update(void);
};

#endif
/*

#pragma once

#include <gl\glut.h>

#define PI			3.1415265359
#define PIdiv180	0.0174529252


#include "../../util/cVector3D.h" 

class cCamera
{
private:
	cVector3D Position;
	cVector3D ViewDir;		//Not used for rendering the camera, but for "moveforwards"
							//So it is not necessary to "actualize" it always. It is only
							//actualized when ViewDirChanged is true and moveforwards is called
	bool ViewDirChanged;
	GLfloat RotatedX, RotatedY, RotatedZ;

	int width,height;
	float speed;

	void GetViewDir (void);

public:
	cCamera();						
	void Init(int w,int h,float s);	//necessary for input updates
	void Look();					//glRotates and a glTranslate command
	
	void Rotate	(cVector3D Angles);
	void Update (bool keys[256], int mouseX, int mouseY);

	void GetPosition(cVector3D *pos);
	void GetRotated(cVector3D *rot);
	void SetPosition(cVector3D pos);
	void MoveForwards(GLfloat distance);

private:
	void RotateX(GLfloat angle);
	void RotateY(GLfloat angle);
	void RotateZ(GLfloat angle);

	void StrafeRight(GLfloat distance);
};

*/