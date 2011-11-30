/*
class cSceneManager: Se encarga de localizar cada escena (Intro, Gameplay, MenúPrincipal...), activarlas y desactivarla
					Init: Inicializar la librería 
					AddSound: Registraremos el sonido y obtendremos el ID del buffer que utilizaremos desde el objeto
					Play: Reproducir el sonido pasando por parámetro el ID
					Stop: Detener el sonido pasado por parámetro
					ActivateSound/DeactivateSound: Activa y desactiva el sonido
					-- ACTUALMENTE EN REFORMAS INTERNAS --
*/

#pragma once

#include "..\Utility\Singleton.h"
#include "Game.h"
#include <vector>
using namespace std;

enum eScenes{
	eMenuPrincipal,
	eIntro,
	eLoading,
	eGameplay,
	eNoDisponible,
	ePausa,
	ePortada,
	eCreditos,
	eHistoria,
	eFinPartida
};

class cSceneManager : public cSingleton<cSceneManager>
{
public:
	bool Init();
	bool Deinit();
	void Render();
	void Update(float lfTimestep); 
	bool LoadScene(eScenes lScene);
	inline eScenes GetScene(){return mActualScene;}
	inline int GetHistoria(){return mHistoria;}
	inline int NextHistoria(){return mHistoria++;}
private:
	eScenes mActualScene;
	int mHistoria; // Utilizaremos este valor para saber en qué punto de la historia estamos, si es 0, es una partida libre
};

