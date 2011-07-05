/*
class cSoundManager: Controla y maneja todos los sonidos que se utilizarán en el juego
					Init: Inicializar la librería 
					AddSound: Registraremos el sonido y obtendremos el ID del buffer que utilizaremos desde el objeto
					Play: Reproducir el sonido pasando por parámetro el ID
					Stop: Detener el sonido pasado por parámetro
					ActivateSound/DeactivateSound: Activa y desactiva el sonido
					-- ACTUALMENTE EN REFORMAS INTERNAS --
*/

#pragma once

#include "..\Utility\Singleton.h"
#include "..\Graphics\Fonts\acgfx_font.h"
#include <vector>
// OpenAL includes
#include"Framework\Framework.h"
using namespace std;
	
struct Sound{
	string Name;
	ALuint Buffer;
	ALuint Source;
};

typedef std::vector<Sound *> mList;

class cSoundManager :
	public cSingleton<cSoundManager>
{
public:
	public:	
		bool Init();
		bool Deinit();
		void Render();
		void Update(float lfTimestep); 
		Sound *AddSound(char *lFileName);
		void Play(Sound *lSound, bool lLoop);
		void Stop(Sound *lSound);
		// Con esto activaremos y desactivaremos el sonido
		inline void ActivateSound(){mIsSoundOn=true;}
		inline void DeactivateSound(){mIsSoundOn=false;}
	private:
		bool mIsSoundOn;

		// Utilizaremos estas listas para tener un control directo con los sonidos que utilizaremos.
		mList mSoundsList;
};

