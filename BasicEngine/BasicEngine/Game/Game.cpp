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
#include "..\Game\Scene\SceneManager.h"
#include "..\Graphics\Meshes\MeshManager.h"
#include "..\Game\Scene\Scene.h"
#include "..\Graphics\Fonts\FontManager.h"
#include "..\Graphics\Materials\MaterialManager.h"
#include "..\Graphics\Effects\EffectManager.h"
#include "..\Graphics\Skeletal\SkeletalManager.h"
#include "..\Graphics\Skeletal\SkeletalMesh.h"


extern tActionMapping kaActionMapping[];


bool cGame::Init() { //Inicializa el juego
	mbFinish = false;
	
	LoadResources();  //Load Resources (nada por ahora, incluse se puede meter el mProperties dentro)
	mProperties.Init();
	//cCharacter *c1, *c2, *c3, *c4; //Personajes. Se comenta porque no se están usando
	
	bool lbResult = cWindow::Get().Init(mProperties);
	if ( lbResult ) { // Init OpenGL
		lbResult = cGraphicManager::Get().Init( &cWindow::Get() );
		if (!lbResult) cWindow::Get().Deinit();	// Kill Window
	}

	cTextureManager::Get().Init(10); //Iniciando las texturas. Espacio reservado máximo para la carga=10
	cCharacterManager::Get().Init(); //Inicializamos el Gestor de Personajes

	//Iniciando la camara
	m3DCamera.Init();
	float lfAspect = (float)mProperties.muiWidth / (float)mProperties.muiHeight;
	m3DCamera.SetPerspective (45.0f, lfAspect,0.1f,100.0f);
	//m3DCamera.SetLookAt (cVec3 (5.0f, 5.f, 5.f), cVec3 (0.0f, 0.f, 0.f), cVec3 (0, 1, 0));
	m3DCamera.SetLookAt( cVec3(0.001f, 10.0f, 0.0f), cVec3(0.0f, 0.0f, 0.0f)); //Cámara en modo cenital (mirando desde arriba)

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

	cLuaManager::Get().Init(); //Init the Lua Manager
	RegisterLuaFunctions(); //Registramos las funciones de C++ que se llamarán desde Lua
	
	// Init Input Manager
	cInputManager::Get().Init( kaActionMapping, eIA_Count );
		
	mFont.Init("./Data/Fonts/Test2.fnt"); // Init the Font
	cFontManager::Get().Init(5);
	mFontHandle = cFontManager::Get().LoadResourcesXml("Fonts");  //cargando desde XML
	//Empezando de nuevo las priebas para la parte opcional de la practica 4 de gestionar las fuentes
	//mFontHandle = cFontManager::Get().LoadResource("Font1", "./Data/Fonts/Test1.fnt");
	//mFontHandle = cFontManager::Get().LoadResource("Font3", "./Data/Fonts/Test3.fnt");
	
	//pruebas para ver si guardo y despues usarlo es esta forma
	//cResource * lpResource = mFontHandle.GetResource();
	//cFont * lpFont = (cFont*)lpResource;

	int liLuaRes = cLuaManager::Get().DoFile(LUA_FILE); //Lua	

	
	cMeshManager::Get().Init(10); // Init MeshManager	
	cSceneManager::Get().Init(10); // Init SceneManager

	cMaterialManager::Get().Init(10); //Init Material Manager
	cEffectManager::Get().Init(10);

	//TODO: SceneManager debe ir despúes de MaterialManager y EffectManager
	//mScene = cSceneManager::Get().LoadResourcesXml("Scenes");  //cargando desde XML el dragon y mas cosas si se ponen //ESTA ES LA QUE USAMOS!!!!
	mScene = cSceneManager::Get().LoadResource("TestLevel", "./Data/Scene/dragonsmall.DAE");  //Para cargarla directamente
	//mScene = cSceneManager::Get().LoadResource("TestLevel", "./Data/Scene/cuboBlender.dae");  //Para cargarla directamente
	//mScene = cSceneManager::Get().LoadResource("TestLevel", "./Data/Scene/cuboMax.DAE");  //Para cargarla directamente
	
	

	
	//Skeletal crea una malla esqueletal (usando un recurso añadido como atributo de la clase) y le establece la animación de “Idle”.
	cSkeletalManager::Get().Init(10);
	cSkeletalManager::Get().LoadResource("Skeleton", "./Data/Skeletal/SkeletonModel.xml");
	mSkeletalMesh = cMeshManager::Get().LoadResource("Skeleton1", "Skeleton", kuiSkeletalMesh);
	cSkeletalMesh* lpSkeletonMesh = (cSkeletalMesh*)mSkeletalMesh.GetResource();
	lpSkeletonMesh->PlayAnim("Idle", 1.0f, 1.0f);

	cResourceHandle lMaterial = cMaterialManager::Get().LoadResource("Skeleton", "./Data/Material/SkeletonMaterial.xml");
	assert(lMaterial.IsValidHandle());
	
	//mObject.Init();
	mObject.AddMesh(mSkeletalMesh, lMaterial);
	cMatrix lMatrix;
	lMatrix.LoadScale(0.01f);
	mObject.SetWorldMatrix(lMatrix);


	mfAcTime = 0.0f;

	return lbResult;
}


bool cGame::Deinit() { //Destructor del juego
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


void cGame::Update(float lfTimestep) { //update del juego
	//hacer el contador de 5 segundos
	//OutputDebugString (lsTime.c_str());
	
	cWindow::Get().Update();
	mfAcTime += lfTimestep;
	//cCharacterManager::Get().Update(lfTimestep);  //Carga del Character de LUA, comentado por ahora
	cInputManager::Get().Update(lfTimestep);

	//Actualizando la mmala del esqueleto
	cSkeletalMesh* lpSkeletonMesh = (cSkeletalMesh*)mSkeletalMesh.GetResource();
	//lpSkeletonMesh->Update(lfTimestep);  //cmentamos esto en los apuntes para poner el mObject
	mObject.Update(lfTimestep);

	static bool mbJogging = false;
	if (BecomePressed( eIA_PlayJog ) && !mbJogging)
	{
		mbJogging = true;
		lpSkeletonMesh->PlayAnim("Jog", 1.0f, 0.1f);
		lpSkeletonMesh->StopAnim("Idle", 0.1f);
	}
	else if (BecomePressed( eIA_StopJog ) && mbJogging)
	{
		mbJogging = false;
		lpSkeletonMesh->PlayAnim("Idle", 1.0f, 0.1f);
		lpSkeletonMesh->StopAnim("Jog", 0.1f);
	}
	if (BecomePressed( eIA_PlayWave ))
	{
		lpSkeletonMesh->PlayAnim("Wave", 1.0f, 0.1f, 0.1f);
	}
	else if (BecomePressed( eIA_StopWave ))
	{
		lpSkeletonMesh->StopAnim("Wave", 0.1f);
	}




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
	m3DCamera.SetLookAt(cVec3(3.0f, 3.0f, 3.0f), cVec3(0.0f, 0.0f, 0.0f) ); //Posicionando la camara
	//RenderTest();
	RenderRejilla(); //muestra la rejilla, solo en modo depuración o DEBUG
	RenderMalla(); //Por ahora dibuja el dragon
	//RenderSkeletal();

	// 4) Render 3D with transparency

	// 5) Activate 2D Camera
	cGraphicManager::Get().ActivateCamera( &m2DCamera );
	//cGraphicManager::Get().RefreshWorldView(); ya esto lo hace el Activate Camera

	// 6) Render 2D Elements
	SetTheWorldMatrix();
	RenderFuentes();	

	// 7) Postprocessing

	// 8) Swap Buffers
	cGraphicManager::Get().SwapBuffer();  // Al final del ciclo de renderizado, volcamos el buffer
}


//FUNCTIONS

//Load all resources, no usada por ahora
void cGame::LoadResources () {}

void cGame::SetTheWorldMatrix() { // Set the world matrix 
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);
}

void cGame::RenderMalla() {
	//glDisable(GL_TEXTURE_2D);
	//m3DCamera.SetLookAt(cVec3(15.0f, 15.0f, 15.0f), cVec3(0.0f, 0.0f, 0.0f) );
	//m3DCamera.SetLookAt(cVec3(3.0f, 3.0f, 3.0f), cVec3(0.0f, 0.0f, 0.0f) );
	((cScene *)mScene.GetResource())->Render();
	//glEnable(GL_TEXTURE_2D);
}

void cGame::RenderSkeletal ()
{
	mObject.Render();
	cSkeletalMesh* lpSkeletonMesh = (cSkeletalMesh*)mSkeletalMesh.GetResource();
	lpSkeletonMesh->RenderSkeleton();
}

void cGame::RenderFuentes () { //Renderizamos una fuente en pantalla siguiendo el orden
	/*
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
	*/

	//Draw some strings
	glEnable(GL_TEXTURE_2D);
	mFont.SetColour( 1.0f, 0.0f, 0.0f );
	mFont.Write(0,200,0, "Año Totó pingüino() ¡!¿?", 0,	FONT_ALIGN_CENTER);
	mFont.SetColour( 0.0f, 1.0f, 1.0f );
	mFont.WriteBox(100,100,0,100, "Esto es un test \nmultilinea", 0,	FONT_ALIGN_CENTER);
}

void cGame::RenderLua () { //Para los ejercicios de LUA
	//Pintar el circuito 
	cLuaManager::Get().CallLua("DrawPath", (int *)NULL);
	cCharacterManager::Get().Render();
}

void cGame::RenderRejilla () { //Renderizamos la rejilla en caso de que sea debug la compilación
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

