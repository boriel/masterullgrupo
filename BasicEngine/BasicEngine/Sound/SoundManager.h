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
		Sound *AddSound(char *lFileName, bool isMusic=false);
		void Play(Sound *lSound, bool lLoop=false);
		void Stop(Sound *lSound);

		// Con esto activaremos y desactivaremos el sonido
		inline bool IsSoundOn(){return mIsSoundOn;}
		inline void ActivateSound(){mIsSoundOn=true;}
		inline void DeactivateSound(){mIsSoundOn=false;}

		inline bool IsMusicOn(){return mIsMusicOn;}
		inline void ActivateMusic(){mIsMusicOn=true;}
		inline void DeactivateMusic(){mIsMusicOn=false;}
		void PlayMusic();
		void ChangeMusic(char *lFileName);
		void StopMusic();
private:
		bool mIsSoundOn;
		bool mIsMusicOn;
		// Utilizaremos estas listas para tener un control directo con los sonidos que utilizaremos.
		mList mSoundsList;
		Sound *mMusic; // Música será distinto a los efectos de sonido. Solo habrá 1 activa.
};

