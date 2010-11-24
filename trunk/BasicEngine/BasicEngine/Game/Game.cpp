//#include <windows.h>


#include "Game.h"

#include "..\Window\Window.h"
#include "..\Graphics\GraphicManager.h"
#include "..\Input\InputManager.h"
#include "InputConfiguration.h"
#include "../Graphics/Textures/TextureManager.h"
#include "../Lua/LuaManager.h"

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

	//Iniciando las texturas
	cTextureManager::Get().Init(2); 


	//Iniciando la camara
	m3DCamera.Init();
	float lfAspect = (float)mProperties.muiWidth / (float)mProperties.muiHeight;
	m3DCamera.SetPerspective (45.0f, lfAspect,0.1f,100.0f);
	m3DCamera.SetLookAt (cVec3 (5.0f, 5.f, 5.f), cVec3 (0.0f, 0.f, 0.f), cVec3 (0, 1, 0));


	//Iniciando Camara 2D
	float lfRight = (float)mProperties.muiWidth / 2.0f;
	float lfLeft = -lfRight;
	float lfTop = (float)mProperties.muiHeight / 2.0f;
	float lfBottom = -lfTop;
	m2DCamera.Init();
	m2DCamera.SetOrtho(lfLeft, lfRight, lfBottom, lfTop, 0.1f, 100.0f);
	//m2DCamera.SetLookAt( cVec3(0.0f, 0.0f, 1.f), cVec3(0.0f, 0.f, 0.f) );
	m2DCamera.SetLookAt( cVec3(0.0f, 0.0f, 1.f), cVec3(0.0f, 0.f, 0.f), cVec3 (0, 1, 0) );

	// Init the Font
	mFont.Init("./Data/Fonts/Test1.fnt");

	// Init the Lua Manager
	cLuaManager::Get().Init();
	
	// Init Input Manager
	cInputManager::Get().Init( kaActionMapping, eIA_Count );
	
	cResourceHandle lRH = cTextureManager::Get().FindResource(".\\Data\\Fonts\\Test1_0.tga");
	//cResourceHandle lRH = cTextureManager::Get().FindResource("Font");
	
	cResource* lResource = lRH.GetResource();
	
	
	return lbResult;
}


//Destrucutor del juego
bool cGame::Deinit()
{
	bool lbResult = cGraphicManager::Get().Deinit();
	lbResult = lbResult && cWindow::Get().Deinit();
	
	cInputManager::Get().Deinit();
	mFont.Deinit();
	cTextureManager::Get().Deinit();
	cLuaManager::Get().Deinit();

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
	/*
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

	*/
	RenderFuentes();

}



//FUNCTIONS

//Load all resources
void cGame::LoadResources ()
{
	
	
	
}


//Rendreizamos una fuente en pantalla siguiendo el orden
void cGame::RenderFuentes ()
{
	// 1) Clean Buffers
	// -------------------------------------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 2) Activate the 3D Camera
	// -------------------------------------------------------------
	cGraphicManager::Get().ActivateCamera( &m3DCamera );

	// 3) Render Solid 3D
	// -------------------------------------------------------------
	// Set the world matrix
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);
	// Render the debug lines
	cGraphicManager::Get().DrawGrid();
	cGraphicManager::Get().DrawAxis();
	cGraphicManager::Get().DrawPoint( cVec3(1.5f, 0.0f, 1.5f),
	cVec3(1.0f, 0.0f, 1.0f) );
	cGraphicManager::Get().DrawLine( cVec3(-1.5f, 0.0f, -1.5f),
	cVec3(-1.5f, 0.0f, 1.5f),
	cVec3(1.0f, 1.0f, 0.0f) );

	// 4) Render 3D with transparency
	// -------------------------------------------------------------

	// 5) Activate 2D Camera
	// -------------------------------------------------------------
	cGraphicManager::Get().ActivateCamera( &m2DCamera );

	// 6) Render 2D Elements
	// -------------------------------------------------------------
	//Draw some strings
	mFont.SetColour (1.0f, 0.0f, 0.0f);
	mFont.Write(0,200,0, "Renderizando algo en cGame-Render-RenderFuentes", 0, FONT_ALIGN_CENTER);

	mFont.SetColour (0.0f, 1.0f, 1.0f);
	mFont.WriteBox(100,100,0, 100, "Renderizando \nvarias \n lineas", 0, FONT_ALIGN_CENTER);


	// 7) Postprocessing
	// -------------------------------------------------------------

	// 8) Swap Buffers
	// -------------------------------------------------------------
	cGraphicManager::Get().SwapBuffer();
}

