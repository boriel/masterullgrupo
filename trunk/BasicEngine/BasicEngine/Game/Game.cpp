
#include "Game.h"

#include "..\Window\Window.h"
#include "Scene\ModelManager.h"
#include "Scene\Model.h"
#include "Object\ObjectManager.h"
#include "Object\ObjectVehicle.h"
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
#include "..\Physics\PhysicsManager.h"
#include "HudManager.h"
#include "FPSCounter.h"
#include "..\Sound\SoundManager.h"
#include "SceneManager.h"
#include "MenuManager.h"
#include "..\Utility\TimeDebug.h"

#include "..\Graphics\Materials/MaterialData.h"

#ifdef _DAVID
#include "..\Lua\LuaManager.h"
#include "..\Lua\LuaFunctions.h"
#include "..\Character\CharacterManager.h"
#include "..\Character\Behaviour\BehaviourManager.h"
#include "..\Character\Behaviour\ChaserBase.h"
#endif

#define MaxSize 200

extern tActionMapping kaActionMapping[];

//Inicializa el juego
bool cGame::Init() 
{ 
	mbFinish = false;
	mbStart = false;
	mbPause = false;

	mProperties.Init();

	// Pantalla completa
	//mProperties.mbFullscreen=true;

	bool lbResult = cWindow::Get().Init(mProperties);
	if ( lbResult ) { // Init OpenGL
		lbResult = cGraphicManager::Get().Init( &cWindow::Get() );
		if (!lbResult) cWindow::Get().Deinit();	// Kill Window
	}

	cTextureManager::Get().Init(200); //Iniciando las texturas. Espacio reservado máximo para la carga=10
	
	//==============
	//Init CAMERA-3D
	//==============
	m3DCamera.Init();
	float lfAspect = (float)mProperties.muiWidth / (float)mProperties.muiHeight;
	m3DCamera.SetPerspective (45.0f, lfAspect, 0.1f, 10000.0f);
	cGraphicManager::Get().ActivateCamera( &m3DCamera );

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

#ifdef _DAVID
	cCharacterManager::Get().Init(); //Inicializamos el Gestor de Personajes
	cLuaManager::Get().Init(); //Init the Lua Manager
	RegisterLuaFunctions(); //Registramos las funciones de C++ que se llamarán desde Lua
	int liLuaRes = cLuaManager::Get().DoFile(LUA_FILE); //Lua	
#endif

	// Init Input Manager
	cInputManager::Get().Init( kaActionMapping, eIA_Count );
	
	cMeshManager::Get().Init(MaxSize); // Init MeshManager	
	cModelManager::Get().Init(MaxSize); // Init ModelManager

	cMaterialManager::Get().Init(MaxSize); //Init Material Manager
	cEffectManager::Get().Init(MaxSize);


	mfAcTime = 0.0f; 
	
	// Los Init se han pasado a LoadRace() ya que en primer lugar ejecutaremos el Menú y desde ahí accederemos a la carrera
	cSoundManager::Get().Init();
	//cSoundManager::Get().ChangeMusic("Entorno.wav");
	cSceneManager::Get().Init();

	// Accedemos directamente al juego
	cSceneManager::Get().LoadScene(ePortada);
	cHudManager::Get().Init("Data/Resources.xml");
	cMenuManager::Get().Init("Data/Resources.xml");
	

	/*
	//Skeletal crea una malla esqueletal (usando un recurso añadido como atributo de la clase) y le establece la animación de “Idle”.
	cSkeletalManager::Get().Init(10);
	cSkeletalManager::Get().LoadResource("Skeleton", "./Data/Skeletal/SkeletonModel.xml");
	mSkeletalMesh = cMeshManager::Get().LoadResource("Skeleton1", "Skeleton", kuiSkeletalMesh);
	cSkeletalMesh* lpSkeletonMesh = (cSkeletalMesh*)mSkeletalMesh.GetResource();
	//lpSkeletonMesh->PlayAnim("Idle", 1.0f, 1.0f);
	lpSkeletonMesh->PlayAnim("Jog", 1.0f, 0.1f);
	
	
	cResourceHandle lMaterial = cMaterialManager::Get().LoadResource("Skeleton",  "./Data/Material/SkeletonMaterial.xml");
	assert(lMaterial.IsValidHandle());
	//mSubModel.Init();
	mSubModel.AddMesh(mSkeletalMesh, lMaterial);
	cMatrix lMatrix;
	lMatrix.LoadScale(0.01f);
	mSubModel.SetLocalMatrix(lMatrix);
	*/


#ifdef _DAVID
	cTimeDebug::Get().Init(10);
#endif

	return lbResult;
}

bool cGame::LoadRace()
{
	// Reiniciamos la física
	cPhysicsManager::Get().Deinit();
	cPhysicsManager::Get().Init();
	// ----------------------
	cObjectManager::Get().Init();
	cRaceControlManager::Get().Init("Data/Resources.xml");
	
	cFPSCounter::Get().Init();
	
	// Solo seleccionamos jugador si es distinto a la campaña
//	if(cSceneManager::Get().GetHistoria()==0){
		//cMenuManager::Get().SeleccionarJugador();
		// Añadimos los comportamientos pertinentes
		for(int liIndex=0;liIndex<cObjectManager::Get().GetCars()->size();liIndex++)
		{
			((cObjectVehicle *)cObjectManager::Get().GetCars()->at(liIndex))->SetBehaviour();
		}
	//}
	
	cMenuManager::Get().SetAviso(true);
	
	return true;
}

bool cGame::StartRace(){
	// Cuando ha terminado todo de cargarse cambiamos la escena a Gameplay
	cSceneManager::Get().LoadScene(eGameplay);

	// Iniciamos la cuenta atrás en el RaceControlManager
	cRaceControlManager::Get().StartRace();
	cSoundManager::Get().ChangeMusic("TemaPrincipal.wav");

	// Ejemplo de ejecutar sonido. Cada objeto tendrá sus sonidos que se inicializarán en su propio Init
	//cSoundManager::Get().Play(cSoundManager::Get().AddSound("Entorno.wav"), true);
	return true;
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
	cModelManager::Get().Deinit();
	cMeshManager::Get().Deinit();
	cInputManager::Get().Deinit();
	cTextureManager::Get().Deinit();

#ifdef _DAVID
	cLuaManager::Get().Deinit();
	cBehaviourManager::Get().Deinit();
	cCharacterManager::Get().Deinit();
#endif

	cSoundManager::Get().Deinit();
	cEffectManager::Get().Deinit();
	m3DCamera.Deinit();
	cHudManager::Get().Deinit();
	cFPSCounter::Get().Deinit();
	cSceneManager::Get().Deinit();
	cMenuManager::Get().Deinit();

#ifdef _DAVID
	cTimeDebug::Get().Deinit();
#endif

	return lbResult;
}

//update del juego
void cGame::Update(float lfTimestep) 
{
#ifdef _DAVID
	cTimeDebug::Get().StartTimer(0,"Game.Update");
#endif

	cFPSCounter::Get().Update(lfTimestep);
	cInputManager::Get().Update(lfTimestep);

	cWindow::Get().Update();
	mfAcTime += lfTimestep;
	//lpSkeletonMesh->Update(lfTimestep);  //cmentamos esto en los apuntes para poner el mObject
	mSubModel.Update(lfTimestep);	

	if((cSceneManager::Get().GetScene()==eFinalHistoria) && BecomePressed(eIA_Accept)){
		// Resetear contadores de juego
		//cRaceControlManager::Get().
		cSceneManager::Get().LoadScene(ePortada);
		cMenuManager::Get().ActivarMusica();
		return;
	}

	if((cSceneManager::Get().GetScene()==eLoading) && BecomePressed(eIA_Accept)){
		this->StartRace();
	}

	// Si la carrera ha finalizado y presionamos Enter, volvemos al menú inicial
	if(cRaceControlManager::Get().isFinalRace() && BecomePressed(eIA_Accept)){
		m3DCamera.ResetAnimacionFinal();
		// Deinicializar las librerías antes de volver al menú
		cObjectManager::Get().VaciarObjetos();
		cRaceControlManager::Get().VaciarObjetos();
		cRaceControlManager::Get().RestartRace();
		if(cSceneManager::Get().GetHistoria()==0){
			cSceneManager::Get().LoadScene(ePortada);
			cMenuManager::Get().IniciarMenu();
			cMenuManager::Get().ActivarMusica();
		}else {
			// Si estamos en la historia, pasamos al siguiente nivel si ha ganado, si no volvemos al menú
			if(cRaceControlManager::Get().GetVictoria()){
				int Map=cSceneManager::Get().NextHistoria();

				if(Map>2){
					// Hay que colocar la pantalla de final de campaña y agradecimiento por jugar y luego volver al menú
					cSceneManager::Get().LoadScene(eFinalHistoria);
					cSceneManager::Get().ResetHistoria();
					//cSceneManager::Get().LoadScene(eMenuPrincipal);
				}else{
					
					//if(Map==2)cRaceControlManager::Get().SetTipoPartida(eContrarreloj);
					if(Map==1)
						cRaceControlManager::Get().SetTipoPartida(e4Jugadores);
					if(Map==2)
						cRaceControlManager::Get().SetTipoPartida(e2Jugadores);
					
					cSceneManager::Get().LoadScene(eLoading);
				}
				
			}else{
				cSceneManager::Get().LoadScene(eMenuPrincipal);
				cMenuManager::Get().ActivarMusica();
			}
		}
	}

	/*
	// Si el modo no está disponible volvemos atrás
	if(cSceneManager::Get().GetScene() == eNoDisponible && BecomePressed(eIA_Accept)){
		cSceneManager::Get().LoadScene(eMenuPrincipal);
	}*/

	if(cSceneManager::Get().GetScene() == eGameplay && !cRaceControlManager::Get().isFinalRace())
	{
		cPhysicsManager::Get().Update(lfTimestep); //Actualizar la física al completo
		cObjectManager::Get().Update(lfTimestep);  //por ahora aqui tb está el movimiento del vehiculo
		cRaceControlManager::Get().Update(lfTimestep);
		// Actualizamos el Hud
		cHudManager::Get().Update(lfTimestep);
	}

	// Actualizamos los menús si son necesarios
	if(cSceneManager::Get().GetScene() == eMenuPrincipal || cSceneManager::Get().GetScene() == eCreditos || cSceneManager::Get().GetScene()==eNoDisponible || cSceneManager::Get().GetScene() == ePausa || cSceneManager::Get().GetScene() == ePortada || cSceneManager::Get().GetScene() == eSeleccionJugador)
		cMenuManager::Get().Update(lfTimestep);
	
	if (BecomePressed(eIA_ChangeModeDebug)) //F9
		cPhysicsManager::Get().CambiarDebugMode();
	
	if (BecomePressed(eIA_ChangeCamera)) //F8
		cObjectManager::Get().ChangeCameraFP();

	if (BecomePressed(eIA_Reload)) //R
		cObjectManager::Get().ReloadVehicle();

	if(cSceneManager::Get().GetScene()==eGameplay && BecomePressed( eIA_CloseApplication )){
		cSceneManager::Get().LoadScene(ePausa);
		cMenuManager::Get().MenuPausa();
	}
	// Check if we need to close the application
	//Estamos actualizando el input manager y además estamos leyendo la entrada para saber si debemos cerrar la ventana porque se ha pulsado la tecla ESC
	//mbFinish = mbFinish || cWindow::Get().GetCloseApplication()	|| cInputManager::Get().GetAction( eIA_CloseApplication ).GetIsPressed();
	mbFinish = mbFinish || cWindow::Get().GetCloseApplication();
	if (mbFinish) return;
#ifdef _DAVID
	cTimeDebug::Get().StopAndEchoTimer(0);
#endif
}

//render del juego
void cGame::Render() 
{ 
#ifdef _DAVID
	cTimeDebug::Get().StartTimer(1,"Game.Render");
#endif
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

	/* ----------------- GAMEPLAY --------------------- */
	if(cSceneManager::Get().GetScene()==eGameplay){
		glEnable(GL_CULL_FACE);

		RenderPhysicsObjects();  //renderizado la fisica de objetos, siempre que este en debug y haya sido seleccionada
		RenderObjects(); //Dibujando con la nueva representacion de objetos

		//RenderSkeletal();

	#ifdef _DAVID
		SetTheWorldMatrix();
		cRaceControlManager::Get().Render();
	#endif
		SetTheWorldMatrix();
		if (cObjectManager::Get().GetCameraFP()) 
			m3DCamera.FollowPlayer();
		else
		  m3DCamera.Update();
		  
		glDisable(GL_CULL_FACE);
	}

	if(cRaceControlManager::Get().isFinalRace() && (cSceneManager::Get().GetScene()==eGameplay)){
		m3DCamera.EndRaceAnimation();
	}
	/* ------------------------------------------------- */

	// 4) Render 3D with transparency
	
	// 5) Activate 2D Camera
	cGraphicManager::Get().ActivateCamera( &m2DCamera );
	
	// 6) Render 2D Elements
	// Aquí renderizaremos nuestro HudManager y MenúManager.
	SetTheWorldMatrix();
	// Solo ponemos el hud si estamos ingame
	if(cSceneManager::Get().GetScene()==eGameplay) cHudManager::Get().Render();
	  cMenuManager::Get().Render();


	// 7) Postprocessing

	// 8) Swap Buffers
	cGraphicManager::Get().SwapBuffer();  // Al final del ciclo de renderizado, volcamos el buffer

#ifdef _DAVID
	cTimeDebug::Get().StopAndEchoTimer(1);
#endif
}


//FUNCTIONS

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


#ifdef _DAVID

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
	// Los ejes y la rejilla solo aparecen en modo de depuración
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);
	cGraphicManager::Get().DrawGrid();
	cGraphicManager::Get().DrawAxis();
}

#endif