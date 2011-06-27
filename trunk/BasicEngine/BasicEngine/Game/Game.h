/*
Clase Game. Representa nuestro juego e implementa una estructura o ciclo de vida como esta:
				Inicializacion - Update - Render - Destrucción
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

class cGame : public cSingleton<cGame> {
	friend class cSingleton<cGame>;

	private: //variables
		bool mbFinish;
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

	public:  //métodos
		bool Init(); // Function to initialize the game
		void Update(float lfTimestep); // Function to update the game
		void Render(); // Function to render the game
		bool Deinit(); // Function to deinitialize the game
		inline bool HasFinished() { return mbFinish; }  // Get if the game finished
		inline void SetFinished (bool lbValue) { mbFinish = lbValue; }
		inline float GetAcumulatedTime() { return mfAcTime; } //calcular el tiempo en segundos desde que comenzó la aplicación a ejecutar
		float mfAcTime; //Tiempo desde que empezó la aplicación. La necesitan los shaders.

	private:  //métodos
		void LoadResources(); //Read resources for the game (window properties)
		void SetTheWorldMatrix();
		// PASADO AL HUDMANAGER: void RenderTexts();
		void RenderRejilla();
		void RenderLua();
		void RenderModels();
		void RenderObjects();
		void RenderSkeletal();
		void RenderPhysicsObjects();
};

#endif