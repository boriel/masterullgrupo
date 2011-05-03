/* File: GraphicManager.cpp */
#include <assert.h>
#include "GraphicManager.h"

bool cGraphicManager::Init (cWindow * lpWindow) {
	bool lbRet = CreateContext (lpWindow);
	
	if (lbRet) InitializeGLState();

	 mpActiveCamera = NULL;
	 mWorldMatrix.LoadIdentity();

	return lbRet;
}

bool cGraphicManager::Deinit() {
	if (mHRC) {
		if (!wglMakeCurrent(NULL,NULL)) {
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(mHRC)) {
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		mHRC = NULL;
	}
	mpWindow = NULL;
	mpActiveCamera = NULL;
	mWorldMatrix  = NULL;

	return true;
}

bool cGraphicManager::CreateContext( cWindow * lpWindow ) { //Crea el contexto de renderizado
	assert(lpWindow);

	static PIXELFORMATDESCRIPTOR lPfp=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		lpWindow->GetBpp(),
		0, 0, 0, 0, 0, 0,
		0,
		0, 0, 0, 0, 0, 0,
		32, 0, 0,
		PFD_MAIN_PLANE,
		0, 0, 0, 0 
	};

	HDC &lDC = lpWindow->GetHDC();
	if (!lDC) {
		Deinit();
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	
	mPixelFormat = ChoosePixelFormat(lDC,&lPfp);
	if (!mPixelFormat) {
		Deinit();
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if(!SetPixelFormat(lDC,mPixelFormat,&lPfp)) {
		Deinit();
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	mHRC = wglCreateContext(lDC);
	if (!mHRC)
	{
		Deinit();
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if(!wglMakeCurrent(lDC,mHRC))
	{
		Deinit();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	
	mpWindow = lpWindow;
	return true;
}

//Establece el estado del Opengl
void cGraphicManager::InitializeGLState()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	unsigned muiWidth = mpWindow->GetWidth();
	unsigned muiHeight = mpWindow->GetHeight();
	glViewport(0, 0, muiWidth, muiHeight);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	float lfAspectRatio = (float)muiWidth/(float)muiHeight;
	gluPerspective(45.0f, lfAspectRatio, 0.1f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void cGraphicManager::SwapBuffer()
{
   if (mpWindow)
   {
      SwapBuffers(mpWindow->GetHDC());
   }
}



//FUNCIONES DE RENDERIZADO AUXILIARES


//Renderizado de un punto
//Primer parámetro: posición donde se renderizará el punto.
//Segundo parámetro: Color en RGB representado entre 0.0 y 1.0
void cGraphicManager::DrawPoint (const cVec3 &lvPosition, const cVec3 &lvColor)
{
	glDisable(GL_TEXTURE_2D);
	
	// POINT
	glPointSize(10);
	glColor3f (lvColor.x, lvColor.y, lvColor.z);
	glBegin(GL_POINTS);
	glVertex3f(lvPosition.x, lvPosition.y, lvPosition.z);
	glEnd ();
	
	glEnable(GL_TEXTURE_2D);
}

//Renderizado de una línea
void cGraphicManager::DrawLine (const cVec3 &lvPosition1, const cVec3 &lvPosition2, const cVec3 &lvColor)
{
	glDisable(GL_TEXTURE_2D);
	
	// LINE
	glLineWidth (1);
	glColor3f (lvColor.x, lvColor.y, lvColor.z);
	glBegin(GL_LINES);
	for (float xtmp = -10.0; xtmp <= 10.0; xtmp += 1.0)
	{
		glVertex3f(lvPosition1.x, lvPosition1.y, lvPosition1.z);
		glVertex3f(lvPosition2.x, lvPosition2.y, lvPosition2.z);
	};

	glEnd ();

	glEnable(GL_TEXTURE_2D);
}


//Renderizado de una circunferencia centrada en lvPosition
//Es en 2D, a lo largo del plano XZ (vista desde "arriba") -- Se podría generalizar
void cGraphicManager::DrawCircle (const cVec3 &lvPosition, float lfRadius, const cVec3 &lvColor)
{
	float lfStep = 1.0 / lfRadius; // Una pequeña corrección de "aliasing"
	float lfNextS;

	for (float s = 0; s < 2 * PI; s = lfNextS) {
		lfNextS = s + lfStep;
		float lfXa = lvPosition.x + cosf(s) * lfRadius;
		float lfZa = lvPosition.z + sinf(s) * lfRadius;
		float lfXb = lvPosition.x + cosf(lfNextS) * lfRadius;
		float lfZb = lvPosition.z + sinf(lfNextS) * lfRadius;
		DrawLine(cVec3(lfXa, lvPosition.y, lfZa), cVec3(lfXb, lvPosition.y, lfZb), lvColor);
	}
}

void cGraphicManager::DrawGrid() { //Renderizado de una malla o rejilla
	glDisable(GL_TEXTURE_2D);

	// GRID
	glLineWidth (1);
	glColor3f (1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	for (float lfxtmp = -10.0; lfxtmp <= 10.0; lfxtmp += 1.0) {
		glVertex3f (lfxtmp, 0.0f,-10.0);
		glVertex3f (lfxtmp, 0.0f, 10.0);
		glVertex3f (-10.0, 0.0f, lfxtmp);
		glVertex3f ( 10.0, 0.0f, lfxtmp);
	};
	glEnd ();
	glEnable(GL_TEXTURE_2D);
}


//Renderizado de los ejes
//Rojo=X, G=Y, B=Z
void cGraphicManager::DrawAxis()
{
	glDisable(GL_TEXTURE_2D);

	// AXIS
	glLineWidth (2);
	glBegin(GL_LINES);

	glColor3f(1.0f, 0.0f, 0.0f); // X Axis
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f); // Y Axis
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f); // Z Axis
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glEnd();

	glEnable(GL_TEXTURE_2D);
}


//Establece la matrix de mundo
void cGraphicManager::SetWorldMatrix (const cMatrix &lMatrix)
{
	mWorldMatrix = lMatrix;
	RefreshWorldView();
}


void cGraphicManager::RefreshWorldView()
{
	// Select The Modelview Matrix
	glMatrixMode (GL_MODELVIEW);
	
	// Calculate the ModelView Matrix
	cMatrix lWorldView = mpActiveCamera->GetView();
	lWorldView = mWorldMatrix * lWorldView;
	
	// Set The View Matrix
	glLoadMatrixf (lWorldView.AsFloatPointer());


	mWVPMatrix = lWorldView * mpActiveCamera->GetProj();
}


//Establecemos la cámara actual
void cGraphicManager::ActivateCamera (cCamera* lpCamera)
{
	assert(lpCamera);
	mpActiveCamera = lpCamera;

	// Select The Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Set The Projection Matrix
	glLoadMatrixf (mpActiveCamera->GetProj().AsFloatPointer());

	// Refresh the worl view matrix
	RefreshWorldView();
}