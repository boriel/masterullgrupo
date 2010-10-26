//#include <windows.h>


#include "Game.h"

#include "..\Window\Window.h"
#include "..\Graphics\GraphicManager.h"
#include "..\Input\InputManager.h"
#include "InputConfiguration.h"

extern tActionMapping kaActionMapping[];


//Inicializa el juego
bool cGame::Init()
{
	mbFinish = false;
	
	LoadResources();  //Load Resources (nada por ahora, incluse se puede meter el mProperties dentro)
	mProperties.Init();

	bool lbResult = cWindow::Get().Init(mProperties);

	// Init OpenGL
	if ( lbResult )
	{
		lbResult = cGraphicManager::Get().Init( &cWindow::Get() );
		
		// Kill Window
		if (!lbResult)
			cWindow::Get().Deinit();
	}

	//Iniciando la camara
	m3DCamera.Init();
	float lfAspect = (float)mProperties.muiWidth / (float)mProperties.muiHeight;
	m3DCamera.SetPerspective (45.0f, lfAspect,0.1f,100.0f);
	m3DCamera.SetLookAt (cVec3 (5.0f, 5.f, 5.f), cVec3 (0.0f, 0.f, 0.f), cVec3 (0, 1, 0));

	// Init Input Manager
	cInputManager::Get().Init( kaActionMapping, eIA_Count );
	
	return lbResult;
}

//Destrucutor del juego
bool cGame::Deinit()
{
	bool lbResult = cGraphicManager::Get().Deinit();
	lbResult = lbResult && cWindow::Get().Deinit();
	
	cInputManager::Get().Deinit();

	return lbResult;
}


//update del juego
void cGame::Update(float lfTimestep)
{
	//hacer el contador de 5 segundos
	//OutputDebugString (lsTime.c_str());
	
	cWindow::Get().Update();

	cInputManager::Get().Update(lfTimestep);

	// Check if we need to close the application
	//Estamos actualizando el input manager y además estamos leyendo la entrada para saber si debemos cerrar la ventana porque se ha pulsado la tecla ESC
	//mbFinish = mbFinish || cWindow::Get().GetCloseApplication()	|| cInputManager::Get().GetAction( eIA_CloseApplication ).GetIsPressed();
	mbFinish = mbFinish || cWindow::Get().GetCloseApplication()	|| IsPressed( eIA_CloseApplication );
	if (mbFinish)
		return;
	
}


//render del juego
void cGame::Render() 
{
	
	//Mostrar el contador

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	// Render Here!!
	cGraphicManager::Get().DrawPoint(cVec3 (0,0,-5), cVec3 (1,0,0)); //Creamos un punto de ejemplo
	cGraphicManager::Get().DrawLine(cVec3 (0,1,-2), cVec3 (1,0,-3), cVec3 (0,1,0)); //creamos un ejemplo de una linea

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activate the 3D Camera
	cGraphicManager::Get().ActivateCamera( &m3DCamera );

	// Set the world matrix
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);

	//lWorld.LoadTranslation (cVec3 (1, 0, -1.5));
	//cGraphicManager::Get().SetWorldMatrix (lWorld);

	// Render the debug lines
	cGraphicManager::Get().DrawGrid();
	cGraphicManager::Get().DrawAxis();

	cGraphicManager::Get().DrawPoint( cVec3(1.5f, 0.0f, 1.5f), cVec3(1.0f, 0.0f, 1.0f) );
	cGraphicManager::Get().DrawLine( cVec3(-1.5f, 0.0f, -1.5f), cVec3(-1.5f, 0.0f, 1.5f), cVec3(1.0f, 1.0f, 0.0f));

	//otros ejes
	lWorld.LoadTranslation (cVec3 (1, 0, -1.5));
	cGraphicManager::Get().SetWorldMatrix (lWorld);

	// Render the debug lines
	cGraphicManager::Get().DrawGrid();
	cGraphicManager::Get().DrawAxis();
	cGraphicManager::Get().SwapBuffer();
}



//FUNCTIONS

//Load all resources
void cGame::LoadResources ()
{
	
	
	
}



