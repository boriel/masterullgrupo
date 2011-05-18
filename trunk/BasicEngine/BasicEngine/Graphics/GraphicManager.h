/*
Class GraphicManager.h
*/

#ifndef GraphicManager_H
#define GraphicManager_H

#include "GLHeaders.h"
#include "..\Utility\Singleton.h"
#include "..\Window\Window.h"
#include "..\MathLib\MathLib.h"
#include "Camera.h"


//class cWindow;
class cGraphicManager : public cSingleton<cGraphicManager> {
friend class cSingleton<cGraphicManager>;
public:
	bool Init (cWindow * lpWindow);
	bool Deinit();
	void SwapBuffer();

	//Funciones auxiliares de renderizado
	void DrawPoint (const cVec3 &lvPosition, const cVec3 &lvColor);
	void DrawLine (const cVec3 &lvPosition1, const cVec3 &lvPosition2, const cVec3 &lvColor);
	void cGraphicManager::DrawCircle (const cVec3 &lvPosition, float lfRadius, const cVec3 &lvColor);
	void DrawGrid();
	void DrawAxis();

	void SetWorldMatrix (const cMatrix &lMatrix);
	cMatrix GetWorldMatrix () { return mWorldMatrix; } //añadida esta línea
	void RefreshWorldView ();
	void ActivateCamera (cCamera* lpCamera);

	//For Opengl 
	cWindow* mpWindow;		// Save the pointer to window that we show
	GLuint mPixelFormat;	// Save pixel format
	HGLRC mHRC;						// Handle del contexto de renderizado de OPENGL

	cCamera* mpActiveCamera;
	cMatrix mWorldMatrix;
	
	cMatrix mWVPMatrix;
	cCamera * GetActiveCamera() { return mpActiveCamera; }
	const cMatrix &GetWVPMatrix() { return mWVPMatrix; }

protected:
	cGraphicManager() { ; } // Protected constructor
	
private:
	bool CreateContext (cWindow * lpWindow);
	void InitializeGLState();
};

#endif