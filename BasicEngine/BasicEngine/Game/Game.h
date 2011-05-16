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
#include "..\Graphics\Fonts\acgfx_font.h"
#include "Scene\Object.h"

// #include "..\Game\Scene\Scene.h"
//TODO
// Fichero de LUA a cargar
#define LUA_FILE "data/scripts/practica7.lua"

class cGame : public cSingleton<cGame> 
{
	friend class cSingleton<cGame>;

	private: 	//variables
		bool mbFinish;
		cApplicationProperties mProperties;
		cCamera m3DCamera;
		cCamera m2DCamera;
		cFont mFont;
		cResourceHandle mCubo;
		cResourceHandle mScene;
		cResourceHandle mFontHandle;

		cResourceHandle mSkeletalMesh;
		cObject mObject;  //nuevo para el skeleton


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

		

	private:  //m�todos
		void LoadResources(); //Read resources for the game (window properties)
		void SetTheWorldMatrix();
		void RenderFuentes();
		void RenderRejilla();
		void RenderLua();
		void RenderMalla();
		void RenderSkeletal();
		//void SkeletalKeyMove();
};

#endif