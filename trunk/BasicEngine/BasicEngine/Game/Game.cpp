//#include <windows.h>


#include "Game.h"

#include "..\Window\Window.h"
#include "..\Graphics\GraphicManager.h"
#include "..\Input\InputManager.h"
#include "InputConfiguration.h"
#include "..\Graphics\Textures\TextureManager.h"
#include "..\Lua\LuaManager.h"
#include "..\Lua\LuaFunctions.h"
#include "..\Character\CharacterManager.h"
#include "..\Character\Behaviour\BehaviourManager.h"
#include "..\Character\Behaviour\ChaserBase.h"
#include "..\Gameplay\Scene\SceneManager.h"
#include "..\Graphics\Meshes\MeshManager.h"
#include "..\Gameplay\Scene\Scene.h"
#include "..\Graphics\Fonts\FontManager.h"
#include "..\Graphics\Materials\MaterialManager.h"
#include "..\Graphics\Effects\EffectManager.h"


extern tActionMapping kaActionMapping[];


//Inicializa el juego
bool cGame::Init()
{
	mbFinish = false;
	
	LoadResources();  //Load Resources (nada por ahora, incluse se puede meter el mProperties dentro)
	mProperties.Init();

	cCharacter *c1, *c2, *c3, *c4; // Personajes

	
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
	cTextureManager::Get().Init(10); //Espacio reservado máximo para la carga

	//Inicializamos el Gestor de Personajes
	cCharacterManager::Get().Init();

	//Iniciando la camara
	m3DCamera.Init();
	float lfAspect = (float)mProperties.muiWidth / (float)mProperties.muiHeight;
	m3DCamera.SetPerspective (45.0f, lfAspect,0.1f,100.0f);
	//m3DCamera.SetLookAt (cVec3 (5.0f, 5.f, 5.f), cVec3 (0.0f, 0.f, 0.f), cVec3 (0, 1, 0));
	

	// Ponemos la cámara en modo cenital (mirando desde arriba)
	m3DCamera.SetLookAt( cVec3(0.001f, 10.0f, 0.0f), cVec3(0.0f, 0.0f, 0.0f));
	


	//Iniciando Camara 2D
	float lfRight = (float)mProperties.muiWidth / 2.0f;
	float lfLeft = -lfRight;
	float lfTop = (float)mProperties.muiHeight / 2.0f;
	float lfBottom = -lfTop;
	
	m2DCamera.Init();
	m2DCamera.SetOrtho(lfLeft, lfRight, lfBottom, lfTop, 0.1f, 100.0f);
	m2DCamera.SetLookAt( cVec3(0.0f, 0.0f, 1.f), cVec3(0.0f, 0.f, 0.f) );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cGraphicManager::Get().ActivateCamera( &m3DCamera );
	
	// Init the Font
	mFont.Init("./Data/Fonts/Test2.fnt");

	// Init the Lua Manager
	cLuaManager::Get().Init();
	//Registramos las funciones de C++ que se llamarán desde Lua
	RegisterLuaFunctions();
	
	// Init Input Manager
	cInputManager::Get().Init( kaActionMapping, eIA_Count );


		
	cFontManager::Get().Init(5);
	mFontHandle = cFontManager::Get().LoadResourcesXml("Fonts");  //cargando desde XML

	//Empezando de nuevo las priebas para la parte opcional de la practica 4 de gestionar las fuentes
	//mFontHandle = cFontManager::Get().LoadResource("Font1", "./Data/Fonts/Test1.fnt");
	//mFontHandle = cFontManager::Get().LoadResource("Font3", "./Data/Fonts/Test3.fnt");
	
	//pruebas para ver si guardo y despues usarlo es esta forma
	//cResource * lpResource = mFontHandle.GetResource();
	//cFont * lpFont = (cFont*)lpResource;
	



	int liLuaRes = cLuaManager::Get().DoFile(LUA_FILE); //Lua

	/* // El siguiente código es de la práctica 2 y se comenta
	// Añade un personaje al gestor
	c1 = cCharacterManager::Get().CreateCharacter();
	c1->Init();

	// Añade un personaje al gestor
	c2 = cCharacterManager::Get().CreateCharacter();
	c2->Init();

	// Añade un personaje al gestor
	c3 = cCharacterManager::Get().CreateCharacter();
	c3->Init();

	// Añade un personaje al gestor
	c4 = cCharacterManager::Get().CreateCharacter();
	c4->Init();
	
	c1->SetPosition(cVec3(2, 0, 0));
	c2->SetPosition(cVec3(0, 0, 2));
	c3->SetPosition(cVec3(2, 0, 2));
	c4->SetPosition(cVec3(5, 0, -5)); // Punto de llegada

	c1->SetActiveBehaviour(cBehaviourManager::Get().CreateBehaviour(eCHASER_NO_ORIENTATION));
	c2->SetActiveBehaviour(cBehaviourManager::Get().CreateBehaviour(eCHASER_SNAP_ORIENTATION));
	c3->SetActiveBehaviour(cBehaviourManager::Get().CreateBehaviour(eCHASER_WITH_ORIENTATION));

	c1->GetActiveBehaviour()->Init(c1);
	c2->GetActiveBehaviour()->Init(c2);
	c3->GetActiveBehaviour()->Init(c3);

	c1->SetSpeed(1.0f);
	c2->SetSpeed(1.0f);
	c3->SetSpeed(1.0f);

	c1->SetAngSpeed(0.5f);	
	c2->SetAngSpeed(0.5f);
	c3->SetAngSpeed(0.5f);

	((cChaserBase *)c1->GetActiveBehaviour())->SetTarget(c4->GetPosition());
	((cChaserBase *)c2->GetActiveBehaviour())->SetTarget(c4->GetPosition());
	((cChaserBase *)c3->GetActiveBehaviour())->SetTarget(c4->GetPosition());
	*/
	

	

  // Init MeshManager
  cMeshManager::Get().Init(10);


	// Init SceneManager
  cSceneManager::Get().Init(10);


	//Init Material Manager
	cMaterialManager::Get().Init(10);
	

	cEffectManager::Get().Init(10);


	mScene = cSceneManager::Get().LoadResourcesXml("Scenes");  //cargando desde XML el dragon y mas cosas si se ponen
	//mScene = cSceneManager::Get().LoadResource("TestLevel", "./Data/Scene/dragonsmall.DAE");
	

	

	mfAcTime = 0.0f;

	return lbResult;
}


//Destrucutor del juego
bool cGame::Deinit()
{
	bool lbResult = cGraphicManager::Get().Deinit();
	lbResult = lbResult && cWindow::Get().Deinit();
	
	cInputManager::Get().Deinit();
	mFont.Deinit();
	cSceneManager::Get().Deinit();
	cMeshManager::Get().Deinit();
	cInputManager::Get().Deinit();
	cTextureManager::Get().Deinit();
	cLuaManager::Get().Deinit();
	cBehaviourManager::Get().Deinit();
	cCharacterManager::Get().Deinit();

	cEffectManager::Get().Deinit();
	
	return lbResult;
}


//update del juego
void cGame::Update(float lfTimestep)
{
	//hacer el contador de 5 segundos
	//OutputDebugString (lsTime.c_str());
	
	cWindow::Get().Update();
	mfAcTime += lfTimestep;
	//cCharacterManager::Get().Update(lfTimestep);  //Carga del Character de LUA, comentado por ahora
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
	// ORDEN DE PINTADO
	// 1) Clean Buffers
	// 2) Activate the 3D Camera
	// 3) Render Solid 3D
	// 4) Render 3D with transparency
	// 5) Activate 2D Camera
	// 6) Render 2D Elements
	// 7) Postprocessing
	// 8) Swap Buffers


	// 1) Clean Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// 2) Activate the 3D Camera
	cGraphicManager::Get().ActivateCamera( &m3DCamera );


	// 3) Render Solid 3D
	SetTheWorldMatrix();
	//RenderTest();
	RenderRejilla(); //muestra la rejilla, solo en modo depuración o DEBUG
	RenderMalla();


	// 4) Render 3D with transparency


	// 5) Activate 2D Camera
	cGraphicManager::Get().ActivateCamera( &m2DCamera );
	//cGraphicManager::Get().RefreshWorldView(); ya esto lo hace el Activate Camera


	// 6) Render 2D Elements
	SetTheWorldMatrix();
	//RenderLua();
	RenderFuentes();	
	//RenderFuentes2();	
	



	// 7) Postprocessing



	// 8) Swap Buffers
	cGraphicManager::Get().SwapBuffer();  // Al final del ciclo de renderizado, volcamos el buffer


}



//FUNCTIONS

//Load all resources, no usada por ahora
void cGame::LoadResources () {}

// Set the world matrix 
void cGame::SetTheWorldMatrix() 
{
	// Set the world matrix 
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);
}

void cGame::RenderMalla()
{

	//glDisable(GL_TEXTURE_2D);
	//m3DCamera.SetLookAt(cVec3(15.0f, 15.0f, 15.0f), cVec3(0.0f, 0.0f, 0.0f) );
	m3DCamera.SetLookAt(cVec3(5.0f, 5.0f, 5.0f), cVec3(0.0f, 0.0f, 0.0f) );
	((cScene *)mScene.GetResource())->Render();
	//glEnable(GL_TEXTURE_2D);
}


//Rendreizamos una fuente en pantalla siguiendo el orden
void cGame::RenderFuentes ()
{
	//Draw some strings
	mFont.SetColour (1.0f, 0.0f, 0.0f);
	mFont.Write(0,200,0, "Pulse ESC o el Botón Izquierdo para salir", 0, FONT_ALIGN_CENTER);

	//mFont.SetColour (0.0f, 1.0f, 1.0f);
	//mFont.WriteBox(100,100,0, 100, "Renderizando \nvarias \n lineas", 0, FONT_ALIGN_CENTER);

	
	//pruebas para ver si guardo y despues usarlo es esta forma
	cResource * lpResource = mFontHandle.GetResource();
	cFont * lpFont = (cFont*)lpResource;
	cFont lFont = *lpFont;
	lFont.SetColour (1.0f, 0.0f, 0.0f);
	lFont.Write(0,-100,0, "Pintando desde el HANDLE de fuentes", 0, FONT_ALIGN_CENTER);
	

}

void cGame::RenderFuentes2 () {
	// 6) Render 2D Elements
	// -------------------------------------------------------------
	//Draw some strings
	glEnable(GL_TEXTURE_2D);
	mFont.SetColour( 1.0f, 0.0f, 0.0f );
	mFont.Write(0,200,0, "Año Totó pingüino() ¡!¿?", 0,	FONT_ALIGN_CENTER);
	mFont.SetColour( 0.0f, 1.0f, 1.0f );
	mFont.WriteBox(100,100,0,100, "Esto es un test \nmultilinea", 0,	FONT_ALIGN_CENTER);
}

//Para los ejercicios de LUA
void cGame::RenderLua ()
{
	//Pintar el circuito 
	cLuaManager::Get().CallLua("DrawPath", (int *)NULL);

	cCharacterManager::Get().Render();

}



//Renderizamos la rejilla en caso de que sea debug la compilación
void cGame::RenderRejilla ()
{
	
#	ifdef _DEBUG
	// Los ejes y la rejilla solo aparecen en modo de depuración
	/*
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);
	*/
	cGraphicManager::Get().DrawGrid();
	cGraphicManager::Get().DrawAxis();
#	endif
}




//testeando los primeros ejercicios del render
void cGame::RenderTest()
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
}