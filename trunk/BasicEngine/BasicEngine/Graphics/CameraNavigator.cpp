#include "CameraNavigator.h"
#include "..\Input\InputManager.h"
#include "..\Game\InputConfiguration.h"

void cCameraNavigator::Init(void) { 
	mpPosition = new cVec3(10.0f, 4.0f, 3.0f);
	mpTarget = new cVec3(0.0f, 0.0f, 0.0f);
	mpMovement= new cVec3(0.0f, 0.0f, 0.0f);

	SetLookAt( (*mpPosition), (*mpTarget));
}

void cCameraNavigator::Deinit(void) {
	delete mpPosition;
	delete mpTarget;
	delete mpMovement;
}

void cCameraNavigator::Update(void) {
	 cInputManager::Get().GetAction( eIA_CloseApplication ).GetIsPressed();

	if (IsPressed (eIA_Advance)) {
		if ((mpPosition->x)<0) mpMovement->x=+0.05f;
		if ((mpPosition->x)>0) mpMovement->x=-0.05f;
	}
	if (IsPressed (eIA_Back)) {
		if ((mpPosition->x)<0 && (mpPosition->x)>-12.0f) mpMovement->x=-0.05f;
		if ((mpPosition->x)>0 && (mpPosition->x)<+12.0f) mpMovement->x=+0.05f;
	}

	float lfPosX = mpPosition->x;
	mpPosition->x += mpMovement->x; 
	if (lfPosX<-12.0f || lfPosX>12.0f)	mpMovement->x=0.f;
	
	SetLookAt( (*mpPosition), (*mpTarget)); 
}
