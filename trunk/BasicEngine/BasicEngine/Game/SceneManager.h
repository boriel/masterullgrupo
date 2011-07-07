/*
class cSceneManager: Se encarga de localizar cada escena (Intro, Gameplay, Men�Principal...), activarlas y desactivarla
					Init: Inicializar la librer�a 
					AddSound: Registraremos el sonido y obtendremos el ID del buffer que utilizaremos desde el objeto
					Play: Reproducir el sonido pasando por par�metro el ID
					Stop: Detener el sonido pasado por par�metro
					ActivateSound/DeactivateSound: Activa y desactiva el sonido
					-- ACTUALMENTE EN REFORMAS INTERNAS --
*/

#pragma once

#include "..\Utility\Singleton.h"
#include "Game.h"
#include <vector>
using namespace std;

enum Scenes{
	MenuPrincipal,
	Intro,
	Loading,
	Gameplay
};

class cSceneManager :
	public cSingleton<cSceneManager>
{
public:
	public:	
		bool Init();
		bool Deinit();
		void Render();
		void Update(float lfTimestep); 
		bool LoadScene(Scenes lScene);
		inline Scenes GetScene(){return mActualScene;}

	private:
		Scenes mActualScene;
};

