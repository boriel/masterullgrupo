
#include "Game.h"

#include "..\Window\Window.h"
#include "Scene\ModelManager.h"
#include "Scene\Model.h"
#include "Object\ObjectManager.h"
#include "Object\RaceControlManager.h"
#include "InputConfiguration.h"
#include "..\Input\InputManager.h"
#include "..\Graphics\GraphicManager.h"
#include "..\Graphics\Textures\TextureManager.h"
#include "..\Graphics\Meshes\MeshManager.h"
#include "..\Graphics\Fonts\FontManager.h"
#include "..\Graphics\Materials\MaterialManager.h"
#include "..\Graphics\Effects\EffectManager.h"
#include "..\Graphics\Skeletal\SkeletalManager.h"
#include "..\Graphics\Skeletal\SkeletalMesh.h"
#include "..\Lua\LuaManager.h"
#include "..\Lua\LuaFunctions.h"
#include "..\Character\CharacterManager.h"
#include "..\Character\Behaviour\BehaviourManager.h"
#include "..\Character\Behaviour\ChaserBase.h"
#include "..\Physics\PhysicsManager.h"

extern tActionMapping kaActionMapping[];

//Inicializa el juego
bool cGame::Init() 
{ 
	mbFinish = false;
	
	LoadResources();  //Load Resources (nada por ahora, incluse se puede meter el mProperties dentro)
	mProperties.Init();
	
	bool lbResult = cWindow::Get().Init(mProperties);
	if ( lbResult ) { // Init OpenGL
		lbResult = cGraphicManager::Get().Init( &cWindow::Get() );
		if (!lbResult) cWindow::Get().Deinit();	// Kill Window
	}

	cTextureManager::Get().Init(20); //Iniciando las texturas. Espacio reservado máximo para la carga=10
	cCharacterManager::Get().Init(); //Inicializamos el Gestor de Personajes

	//==============
	//Init CAMERA-3D
	//==============
	m3DCamera.Init();
	float lfAspect = (float)mProperties.muiWidth / (float)mProperties.muiHeight;
	m3DCamera.SetPerspective (45.0f, lfAspect, 0.1f, 200.0f);
	
	//===================
	//Iniciando Camara 2D
	//===================
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
	
	int liLuaRes = cLuaManager::Get().DoFile(LUA_FILE); //Lua	
	
	cMeshManager::Get().Init(64); // Init MeshManager	
	cModelManager::Get().Init(64); // Init SceneManager

	cMaterialManager::Get().Init(64); //Init Material Manager
	cEffectManager::Get().Init(64);
	
	//Skeletal crea una malla esqueletal (usando un recurso añadido como atributo de la clase) y le establece la animación de “Idle”.
	cSkeletalManager::Get().Init(10);
	cSkeletalManager::Get().LoadResource("Skeleton", "./Data/Skeletal/SkeletonModel.xml");
	mSkeletalMesh = cMeshManager::Get().LoadResource("Skeleton1", "Skeleton", kuiSkeletalMesh);
	cSkeletalMesh* lpSkeletonMesh = (cSkeletalMesh*)mSkeletalMesh.GetResource();
	lpSkeletonMesh->PlayAnim("Idle", 1.0f, 1.0f);

	cResourceHandle lMaterial = cMaterialManager::Get().LoadResource("Skeleton", "./Data/Material/SkeletonMaterial.xml");
	assert(lMaterial.IsValidHandle());
	
	//mSubModel.Init();
	mSubModel.AddMesh(mSkeletalMesh, lMaterial);
	cMatrix lMatrix;
	lMatrix.LoadScale(0.01f);
	mSubModel.SetLocalMatrix(lMatrix);

	mfAcTime = 0.0f;

	//Pruebas Yorman
	cPhysicsManager::Get().Init();  //Configuracion del mundo fisico (no los objetos)
	cObjectManager::Get().Init();
	cRaceControlManager::Get().Init("Data/Resources.xml");

	return lbResult;
}

//Destructor del juego
bool cGame::Deinit() 
{ 
	bool lbResult = cGraphicManager::Get().Deinit();
	lbResult = lbResult && cWindow::Get().Deinit();
	
	cRaceControlManager::Get().Deinit();
	cPhysicsManager::Get().Deinit();
	cObjectManager::Get().Deinit();

	cInputManager::Get().Deinit();
	mFont.Deinit();
	cModelManager::Get().Deinit();
	cMeshManager::Get().Deinit();
	cInputManager::Get().Deinit();
	cTextureManager::Get().Deinit();
	cLuaManager::Get().Deinit();
	cBehaviourManager::Get().Deinit();
	cCharacterManager::Get().Deinit();

	cEffectManager::Get().Deinit();
	m3DCamera.Deinit();

	return lbResult;
}

//update del juego
void cGame::Update(float lfTimestep) 
{
	cInputManager::Get().Update(lfTimestep);
	//Actualizando la mmala del esqueleto
	cSkeletalMesh* lpSkeletonMesh = (cSkeletalMesh*)mSkeletalMesh.GetResource();

	cPhysicsManager::Get().Update(lfTimestep); //Actualizar la física al completo
	
	cWindow::Get().Update();
	mfAcTime += lfTimestep;
	//lpSkeletonMesh->Update(lfTimestep);  //cmentamos esto en los apuntes para poner el mObject
	mSubModel.Update(lfTimestep);	
	cObjectManager::Get().Update(lfTimestep);  //por ahora aqui tb está el movimiento del vehiculo

	static bool mbJogging = false;
	if (BecomePressed( eIA_PlayJog ) && !mbJogging) 
	{
		mbJogging = true;
		lpSkeletonMesh->PlayAnim("Jog", 1.0f, 0.1f);
		lpSkeletonMesh->StopAnim("Idle", 0.1f);
	} else if (BecomePressed( eIA_StopJog ) && mbJogging) 
	{
		mbJogging = false;
		lpSkeletonMesh->PlayAnim("Idle", 1.0f, 0.1f);
		lpSkeletonMesh->StopAnim("Jog", 0.1f);
	}
	if (BecomePressed( eIA_PlayWave )) 
	{
		lpSkeletonMesh->PlayAnim("Wave", 1.0f, 0.1f, 0.1f);
	} else if (BecomePressed( eIA_StopWave )) 
	{
		lpSkeletonMesh->StopAnim("Wave", 0.1f);
	}

	if (BecomePressed(eIA_ChangeModeDebug)) //F9
	{
		cPhysicsManager::Get().CambiarDebugMode();
	}

	// Check if we need to close the application
	//Estamos actualizando el input manager y además estamos leyendo la entrada para saber si debemos cerrar la ventana porque se ha pulsado la tecla ESC
	//mbFinish = mbFinish || cWindow::Get().GetCloseApplication()	|| cInputManager::Get().GetAction( eIA_CloseApplication ).GetIsPressed();
	mbFinish = mbFinish || cWindow::Get().GetCloseApplication()	|| IsPressed( eIA_CloseApplication );
	if (mbFinish) return;
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

	//RenderTest();
	RenderRejilla(); //muestra la rejilla, solo en modo depuración o DEBUG
	//RenderMalla(); //Por ahora dibuja el dragon, pero con los resources
	//RenderSkeletal();
	RenderPhysicsObjects();  //renedrizado la fisica de objetos, siempre que este en debug y haya sido seleccionada
	RenderObjects(); //Dibujando con la nueva representacion de objetos
	
#ifdef _DEBUG
	cRaceControlManager::Get().Render();
#endif
	SetTheWorldMatrix();
	m3DCamera.Update();
	//m3DCamera.FollowPlayer();  

	// 4) Render 3D with transparency

	// 5) Activate 2D Camera
	cGraphicManager::Get().ActivateCamera( &m2DCamera );
	//cGraphicManager::Get().RefreshWorldView(); ya esto lo hace el Activate Camera

	// 6) Render 2D Elements
	SetTheWorldMatrix();
	RenderTexts();	

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
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);
}

//Dibujamos Todos los objetos
void cGame::RenderObjects () 
{
#if _DEBUG
	if (!cPhysicsManager::Get().GetDebugMode())
		cObjectManager::Get().Render();
#else
	cObjectManager::Get().Render();
#endif

}

//Dibujamos Todos los objetos
void cGame::RenderPhysicsObjects () 
{
#if _DEBUG
	if (cPhysicsManager::Get().GetDebugMode())
		cPhysicsManager::Get().Render();
#endif
}

void cGame::RenderModels() 
{	
	unsigned int luiNextkey = cModelManager::Get().GetNextKey();
	for (unsigned int i = 0; i < luiNextkey - 1; i++)
		((cModel *)cModelManager::Get().FindResourceIndice(i).GetResource())->Render(cGraphicManager::Get().GetWorldMatrix());
}

void cGame::RenderSkeletal () 
{
	mSubModel.Render(cGraphicManager::Get().GetWorldMatrix());
	cSkeletalMesh* lpSkeletonMesh = (cSkeletalMesh*)mSkeletalMesh.GetResource();
	lpSkeletonMesh->RenderSkeleton();
}

//Renderizamos una fuente en pantalla siguiendo el orden
void cGame::RenderTexts() 
{ 
	//Draw some strings
	glEnable(GL_TEXTURE_2D);
	mFont.SetColour( 1.0f, 1.0f, 1.0f );
	mFont.Write(0, 200, 0, "ESC o botón izquierdo para Salir", 0,	FONT_ALIGN_CENTER);
	//mFont.SetColour( 0.0f, 1.0f, 1.0f );
	mFont.Write(0, -200, 0, "Cursor = Vehicle Move -- Q,A,S,D: God Camera", 0,	FONT_ALIGN_CENTER);
	mFont.Write(0, -220, 0, "F9 = Debug", 0,	FONT_ALIGN_CENTER);
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

