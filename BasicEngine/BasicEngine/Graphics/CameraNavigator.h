/*
	Clase C�mara con navegaci�n por el mundo
*/

#ifndef _CAMERA_NAVIGATOR_H
#define _CAMERA_NAVIGATOR_H

#include "Camera.h"

class cCameraNavigator : public cCamera {
	private:
		cVec3 *mpPosition;
		cVec3 *mpTarget;
		cVec3 *mpMovement;

	public:
		void Init(void);
		void Deinit(void);
		void Update(void);
};

#endif