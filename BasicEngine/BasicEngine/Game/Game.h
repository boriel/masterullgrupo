/*
Clase Game. Representa nuestro juego e implementa una estructura o ciclo de vida como esta:
				Inicializacion - Update - Render - Destrucci�n
*/

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include "..\Utility\Singleton.h"
#include "..\Window\ApplicationProperties.h"
#include "..\Graphics\Camera.h"
#include "..\Graphics\CameraNavigator.h"
#include "..\Graphics\Fonts\acgfx_font.h"
#include "Scene\SubModel.h"

// Fichero de LUA a cargar
#define LUA_FILE "data/scripts/practica7.lua"

// Se utilizaran para recolocar bien las string cuando se cambie de resolucion
#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 640

class cGame : public cSingleton<cGame> {
	friend class cSingleton<cGame>;

	private: //variables
		bool mbFinish; // Controlar� el fin de la partida
		bool mbStart; // Controlar� si la partida ha empezado o no
		bool mbPause; // Controlar� si la partida se ha pausado.
		cApplicationProperties mProperties;
		cCameraNavigator m3DCamera;
		cCamera m2DCamera;
		// PASADO AL HUDMANAGER: cFont mFont;
		cResourceHandle mCubo;
		cResourceHandle mScene;
		// PASADO AL HUDMANAGER: cResourceHandle mFontHandle;
		cResourceHandle mSkeletalMesh;
		cSubModel mSubModel;  //nuevo para el skeleton
		//cFPSCounter mFPS;

	protected:
		cGame () { ; } //Protected Constructor

	public:  //m�todos
		bool Init(); // Function to initialize the game
		void Update(float lfTimestep); // Function to update the game
		void Render(); // Function to render the game
		bool Deinit(); // Function to deinitialize the game
		inline bool HasFinished() { return mbFinish; }  // Get if the game finished
		inline void SetFinished (bool lbValue) { mbFinish = lbValue; }
		inline float GetAcumulatedTime() { return mfAcTime; } //calcular el tiempo en segundos desde que comenz� la aplicaci�n a ejecutar
		float mfAcTime; //Tiempo desde que empez� la aplicaci�n. La necesitan los shaders.
		bool LoadRace(); // Cargar� la carrera cuando sea necesario
		bool StartRace();
	private:  //m�todos
		void SetTheWorldMatrix();
		void RenderModels();
		void RenderObjects();
		void RenderPhysicsObjects();
		void RenderSkeletal();
#ifdef _DAVID
		
		void RenderLua();
		void RenderRejilla();
#endif
};

#endif