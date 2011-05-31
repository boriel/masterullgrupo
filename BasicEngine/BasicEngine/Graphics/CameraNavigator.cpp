#include "CameraNavigator.h"

void cCameraNavigator::Init(void) { 
	mpPosition = new cVec3(10.0f, 4.0f, 3.0f);
	mpTarget = new cVec3(0.0f, 0.0f, 0.0f);
	mfDespX=0.00f;

	SetLookAt( (*mpPosition), (*mpTarget));
}

void cCameraNavigator::Deinit(void) {
	delete mpPosition;
	delete mpTarget;
}

void cCameraNavigator::Update(void) {
	/*	if (BecomePressed (eIA_Advance)) {
		if ((mpCamera3DPosition->x)<0) mfDespX=+0.05f;
		if ((mpCamera3DPosition->x)>0) mfDespX=-0.05f;
	}
	if (BecomePressed (eIA_Back)) {
		if ((mpCamera3DPosition->x)<0 && (mpCamera3DPosition->x)>-12.0f) mfDespX=-0.05f;
		if ((mpCamera3DPosition->x)>0 && (mpCamera3DPosition->x)<+12.0f) mfDespX=+0.05f;
	}
	//TODO. [David] Pruebas de cámara
	float lfPosX = mpCamera3DPosition->x;
	mpCamera3DPosition->x = lfPosX+mfDespX; 
	if (lfPosX<-12.0f || lfPosX>12.0f)	mfDespX=0.f;
	*/
	SetLookAt( (*mpPosition), (*mpTarget));  //Cámara en movimiento
}
